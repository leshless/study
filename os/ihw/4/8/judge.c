#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <threads.h>
#include <pthread.h>
#include <string.h>

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

enum input_type {
    INPUT_ARGS,
    INPUT_CLI,
    INPUT_FILE,
};
typedef enum input_type input_type;

struct program_config {
    input_type input_type;
    char* input_file;
    int player_number;
    char* output_file;
};
typedef struct program_config program_config; 

// Global variables (for graceful termination convenience)
shared_data* game_data;
int* player_scores;


char* input_flag = "-i";
char* output_flag = "-o";

// Player thread funcs (two funcs are redundant but ok)
void* player1(void* arg) {
    srand((time(NULL) + pthread_self()) % RAND_MAX);
    move player_move = (move)(rand() % 3);

    game_data->player1_move = player_move;
    
    printf("[%ld] Player 1 has chosen the move %s\n", pthread_self(), move_string[player_move]);
    
    sem_post(&game_data->player1_sem);

    return NULL;
}

void* player2(void* arg) {
    srand((time(NULL) + pthread_self()) % RAND_MAX);
    move player_move = (move)(rand() % 3);

    game_data->player2_move = player_move;
    
    printf("[%ld] Player 2 has chosen the move %s\n", pthread_self(), move_string[player_move]);
    
    sem_post(&game_data->player2_sem);

    return NULL;
}

// Cleanup resources function to be called before exit
void cleanup() {
    free(player_scores);
    sem_destroy(&game_data->player1_sem); 
    sem_destroy(&game_data->player2_sem);
    free(game_data);
}

// SIGINT/SIGTERM handler
void signal_handler(int signal) {
    printf("Recieved interruption signal %d, finishing gracefully\n", signal);

    // Perform cleanup actions
    cleanup();
    exit(0);
}

program_config* parse_cli_args(int argc, char* argv[]) {
    program_config* config = malloc(sizeof(program_config));
    config->input_type = INPUT_CLI;
    config->input_file = NULL;
    config->output_file = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(input_flag, argv[i]) == 0) {
            if (i == argv-1) {
                free(config);
                return NULL;
            }
        }
        if (strcmp(output_flag, argv[i]) == 0) {
            if (i == argv-1) {
                free(config);
                return NULL;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Get the number of players
    int players_amount;
    if (argc != 2) {
        printf("Number of players should be provided\n");
        exit(1);
    }
    
    int players_amount = atoi(argv[1]);
    if (players_amount <= 1) {
        printf("Number of players should be not less than 2\n");
        exit(1);
    }

    // Register signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("[%ld] Starting the rock-paper-scissors tournament\n", pthread_self());
    
    // Allocate array for player scores
    player_scores = (int*)malloc(sizeof(int) * players_amount);
    for (int i = 0; i < players_amount; i++) {
        player_scores[i] = 0;
    }

    // Allocate game data object
    game_data = malloc(sizeof(shared_data));
        
    // Initialize semaphores
    sem_init(&game_data->player1_sem, 1, 0); 
    sem_init(&game_data->player2_sem, 1, 0);
    for (int i = 0; i < players_amount; i++) {
        
        for (int j = i+1; j < players_amount; j++) {
            printf("[%ld] Initializing game between players %d and %d\n", pthread_self(), i, j);

            // Run player threads
            pthread_t thread_id;

            pthread_create(&thread_id, NULL, player1, NULL);
            printf("[%ld] Started first player thread (thread_id = %ld)\n", pthread_self(), thread_id);
            pthread_create(&thread_id, NULL, player2, NULL);
            printf("[%ld] Started second player thread (thread_id = %ld)\n", pthread_self(), thread_id);

            // Wait for players to choose their moves
            sem_wait(&game_data->player1_sem);
            sem_wait(&game_data->player2_sem);

            // Determine the winner / draw
            move player1_move = game_data->player1_move;
            move player2_move = game_data->player2_move;

            if (player1_move == player2_move) {
                player_scores[i] += 1;
                player_scores[j] += 1;

                printf("[%ld] Draw between players %d and %d\n", pthread_self(), i, j);
            } else if (player1_move == (player2_move + 1) % 3) {
                player_scores[i] += 2;

                printf("[%ld] Player %d has defeated player %d\n", pthread_self(), i, j);
            } else {
                player_scores[j] += 2;

                printf("[%ld] Player %d has defeated player %d\n", pthread_self(), j, i);
            }
        }
    }

    // Determine the final winner
    int max_score = 0;
    int winner_number;
    for (int i = 0; i < players_amount; i++) {
        if (player_scores[i] > max_score) {
            max_score = player_scores[i];
            winner_number = i;
        }
    }

    printf("[%ld] Winner of the tournament is player %d with total score of %d\n", pthread_self(), winner_number, max_score);

    cleanup();
}