#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "common.h"

char shm_object_name[50];
char request_sem_name[50];
char response_sem_name[50];
shared_data* player_data;
sem_t* request_sem;
sem_t* response_sem;

void cleanup() {
    sem_unlink(request_sem_name);
    sem_unlink(response_sem_name);
    munmap(player_data, sizeof(shared_data));
    shm_unlink(shm_object_name);
}

void signal_handler(int signal) {
    printf("Recieved interruption signal %d, finishing gracefully\n", signal);

    // Perform cleanup actions
    cleanup();
    exit(0);
}

int main() {
    srand(getpid());

    strcpy(shm_object_name, SHM_OBJECT_PREFIX);
    char pid_string[10];
    
    // Evaluate shared memory object name
    sprintf(pid_string, "%d", getpid());
    strcat(shm_object_name, pid_string);

    // Create shared memory object
    int shm_fd = shm_open(shm_object_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));
    player_data = (shared_data*)mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    // Evaluate named semaphore names
    strcpy(request_sem_name, REQUEST_SEM_PREFIX);
    strcat(request_sem_name, pid_string);
    strcpy(response_sem_name, RESPONSE_SEM_PREFIX);
    strcat(response_sem_name, pid_string);

    // Create named semaphores
    request_sem = sem_open(request_sem_name, O_CREAT, 0666, 0);
    response_sem = sem_open(response_sem_name, O_CREAT, 0666, 0);

    // Register signal hanlders
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("Listenning for judge's commands\n");
    
    while (1) {
        // Wait until the judge tells us to do our turn 
        sem_wait(request_sem);

        printf("Got signal from the judge, generating next move\n");

        // If the tournament is over we should break and terminate
        if (player_data->tournament_over) {
            break;
        }

        // Generate our next move
        player_data->player_move = (move)(rand() % 3);
        
        printf("Throwing %s move\n", move_string[player_data->player_move]);

        // Report we are done
        sem_post(response_sem);
    }

    printf("Tournament is over, finishing\n");
    
    cleanup();
}