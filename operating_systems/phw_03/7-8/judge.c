#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "common.h"

#define MAX_PLAYERS_QUANTITY 50

int players_quantity = 0;
int player_scores[MAX_PLAYERS_QUANTITY];
shared_data* player_datas[MAX_PLAYERS_QUANTITY];
sem_t* request_sems[MAX_PLAYERS_QUANTITY];
sem_t* response_sems[MAX_PLAYERS_QUANTITY];

void cleanup() {
    for (int i = 0; i < players_quantity; i++) {
        sem_close(request_sems[i]);
        sem_close(response_sems[i]);
        munmap(player_datas[i], sizeof(shared_data));
    }
}

void signal_handler(int signal) {
    printf("Recieved interruption signal %d, finishing gracefully\n", signal);

    // Perform cleanup actions
    cleanup();
    exit(0);
}

int main() {
    printf("Discovering ready players\n");

    DIR* dir = opendir("/dev/shm");
    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        // Find shm objects that are obviously our players ready to play
        if (strstr(entry->d_name, SHM_OBJECT_PREFIX) == entry->d_name) {
            // Eval player pid
            char player_pid_string[10];
            strcpy(player_pid_string, entry->d_name + strlen(SHM_OBJECT_PREFIX));

            printf("Found player: %s\n", player_pid_string);

            // Open shared memory object
            int fd = shm_open(entry->d_name, O_RDWR, 0);
            shared_data* player_data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            player_datas[players_quantity] = player_data;
            close(fd);

            // Evaluate semaphore names
            char request_sem_name[50];
            strcpy(request_sem_name, REQUEST_SEM_PREFIX);
            strcat(request_sem_name, player_pid_string);

            char response_sem_name[50];
            strcpy(response_sem_name, RESPONSE_SEM_PREFIX);
            strcat(response_sem_name, player_pid_string);
            
            // Open semaphores
            sem_t* request_sem = sem_open(request_sem_name, O_CREAT, 0666, 0);
            request_sems[players_quantity] = request_sem;

            sem_t* response_sem = sem_open(response_sem_name, O_CREAT, 0666, 0);
            response_sems[players_quantity] = response_sem;

            players_quantity++;
            if (players_quantity == MAX_PLAYERS_QUANTITY) {
                printf("Max players amount reached, some players may be ignore\n");
                break;
            }
        }
    }
    closedir(dir);

    // Register signal hanlders
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if (players_quantity < 2) {
        printf("Not enough players to start the tournament\n");
        
        cleanup();
        return 0;
    }

    printf("Found %d ready players, starting the tournament\n", players_quantity);

    for (int i = 0; i < players_quantity; i++) {
        for (int j = i+1; j < players_quantity; j++) {
            printf("Initializing game between players %d and %d\n", i, j);

            // Post in players channels for them to do a move
            sem_post(request_sems[i]);
            sem_post(request_sems[j]);

            // Wait for players to choose their moves
            sem_wait(response_sems[i]);
            sem_wait(response_sems[j]);

            // Determine the winner / draw
            move player1_move = player_datas[i]->player_move;
            move player2_move = player_datas[j]->player_move;

            if (player1_move == player2_move) {
                player_scores[i] += 1;
                player_scores[j] += 1;

                printf("Draw between players %d and %d\n", i, j);
            } else if (player1_move == (player2_move + 1) % 3) {
                player_scores[i] += 2;

                printf("Player %d has defeated player %d\n", i, j);
            } else {
                player_scores[j] += 2;

                printf("Player %d has defeated player %d\n", j, i);
            }
        }
    }

    // Report to players that tournament is over
    for (int i = 0; i < players_quantity; i++) {
        player_datas[i]->tournament_over = 1;
        sem_post(request_sems[i]);   
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

    printf("Winner of the tournament is player %d with total score of %d\n", winner_number, max_score);

    cleanup();
}