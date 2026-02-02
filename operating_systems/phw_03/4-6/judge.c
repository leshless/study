#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

enum move {
    ROCK,
    PAPER,
    SCISSORS,
};
typedef enum move move;

const char* move_string[] = {
    "ROCK",
    "PAPER",
    "SCISSORS", 
};

struct shared_data {
    sem_t player1_sem;
    sem_t player2_sem;
    enum move player1_move;
    enum move player2_move;
};
typedef struct shared_data shared_data;

const char* SHM_OBJECT_NAME = "rock_paper_scissors";

// Global variables (for graceful termination convenience)
shared_data* game_data;
int* player_scores;
short is_child = 0;

int player1(shared_data* game_data, int player_number) {
    srand((time(NULL) + player_number) % RAND_MAX);
    move player_move = (move)(rand() % 3);
    game_data->player1_move = player_move;

    printf("[%d] Player %d has chosen the move %s\n", getpid(), player_number, move_string[player_move]);
    
    sem_post(&game_data->player1_sem);
    return 0;
}

int player2(shared_data* game_data, int player_number) {
    move player_move = (move)(rand() % 3);
    game_data->player2_move = player_move;

    printf("[%d] Player %d has chosen the move %s\n", getpid(), player_number, move_string[player_move]);
    
    sem_post(&game_data->player2_sem);
    return 0;
}

void cleanup() {
    free(player_scores);
    sem_destroy(&game_data->player1_sem); 
    sem_destroy(&game_data->player2_sem);
    munmap(game_data, sizeof(shared_data));
    shm_unlink(SHM_OBJECT_NAME);
}

void signal_handler(int signal) {
    printf("Recieved interruption signal %d, finishing gracefully\n", signal);

    // Protection JiC if we are in child process
    if (is_child) {
        exit(0);
    }

    // Wait for subprocesses
    wait(NULL);
    wait(NULL);

    // Perform cleanup actions
    cleanup();
    exit(0);
}

int main(int argc, char* argv[]) {
    // Get the number of players
    if (argc != 2) {
        printf("Number of players should be provided\n");
        exit(1);
    }
    int players_quantity = atoi(argv[1]);
    if (players_quantity <= 1) {
        printf("Number of players should be not less than 2\n");
        exit(1);
    }

    // Register signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("[%d] Starting the rock-paper-scissors tournament\n", getpid());

    // Allocate array for player scores
    player_scores = (int*)malloc(sizeof(int) * players_quantity);
    for (int i = 0; i < players_quantity; i++) {
        player_scores[i] = 0;
    }

    // Create shared memory object for processes
    int shm_fd = shm_open(SHM_OBJECT_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));
    game_data = (shared_data*)mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    // Initialize semaphores
    sem_init(&game_data->player1_sem, 1, 0); 
    sem_init(&game_data->player2_sem, 1, 0);

    for (int i = 0; i < players_quantity; i++) {
        for (int j = i+1; j < players_quantity; j++) {
            printf("[%d] Initializing game between players %d and %d\n", getpid(), i, j);

            // Fork players processes
            if (fork() == 0) {
                is_child = 1;
                return player1(game_data, i);
            }
            if (fork() == 0) {
                is_child = 1;
                return player2(game_data, j);
            }
            
            // Wait for players to choose their moves
            sem_wait(&game_data->player1_sem);
            sem_wait(&game_data->player2_sem);

            // JiC, wait for processes to finish
            wait(NULL);
            wait(NULL);

            // Determine the winner / draw
            move player1_move = game_data->player1_move;
            move player2_move = game_data->player2_move;

            if (player1_move == player2_move) {
                player_scores[i] += 1;
                player_scores[j] += 1;

                printf("[%d] Draw between players %d and %d\n", getpid(), i, j);
            } else if (player1_move == (player2_move + 1) % 3) {
                player_scores[i] += 2;

                printf("[%d] Player %d has defeated player %d\n", getpid(), i, j);
            } else {
                player_scores[j] += 2;

                printf("[%d] Player %d has defeated player %d\n", getpid(), j, i);
            }
        }
    }

    // Determine the final winner
    int max_score = 0;
    int winner_number;
    for (int i = 0; i < players_quantity; i++) {
        if (player_scores[i] > max_score) {
            max_score = player_scores[i];
            winner_number = i;
        }
    }

    printf("[%d] Winner of the tournament is player %d with total score of %d\n", getpid(), winner_number, max_score);

    cleanup();
}