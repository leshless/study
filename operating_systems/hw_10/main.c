#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <threads.h>
#include <pthread.h>

#define GENERATORS_AMOUNT 3
#define GENERATED_NUMBER_MIN 1
#define GENERATED_NUMBER_MAX 100
#define GENERATED_NUMBERS_AMOUNT 1
#define GENERATOR_SLEEP_TIME_MIN 1
#define GENERATOR_SLEEP_TIME_MAX 1
#define SUMMATOR_SLEEP_TIME_MIN 1
#define SUMMATOR_SLEEP_TIME_MAX 1

struct summator_args {
    int number1;
    int number2; 
};
typedef struct summator_args summator_args;

int pipe_write_fd;
int pipe_read_fd;

void* generator() {
    for (int i = 0; i < GENERATED_NUMBERS_AMOUNT; i++) {
        printf("[%ld] Generating numbers...\n", pthread_self());

        int sleep_time = rand() % (GENERATOR_SLEEP_TIME_MAX - GENERATOR_SLEEP_TIME_MIN + 1) + GENERATOR_SLEEP_TIME_MIN;
        sleep(sleep_time);

        int number = rand() % (GENERATED_NUMBER_MAX - GENERATED_NUMBER_MIN + 1) + GENERATED_NUMBER_MIN;
        write(pipe_write_fd, &number, sizeof(int));

        printf("[%ld] Generated and pushed to pipe number %d on %dth iteration\n", pthread_self(), number, i+1);
    }

    printf("[%ld] Finished generating numbers\n", pthread_self());
}

void* summator(void* arg) {
    printf("[%ld] Summing numbers...\n", pthread_self());

    int sleep_time = rand() % (SUMMATOR_SLEEP_TIME_MAX - SUMMATOR_SLEEP_TIME_MIN + 1) + SUMMATOR_SLEEP_TIME_MIN;
    sleep(sleep_time);

    summator_args* args = (summator_args*)(arg);
    int result = args->number1 + args->number2;
    write(pipe_write_fd, &result, sizeof(int));

    printf("[%ld] Evaluated and pushed to pipe sum %d+%d=%d\n", pthread_self(), args->number1, args->number2, result);

    free(arg);
}

int main() {
    int pipe_fd[2];
    pipe(pipe_fd);

    printf("[%ld] Created OS pipe for threads\n", pthread_self());

    pipe_read_fd = pipe_fd[0];
    pipe_write_fd = pipe_fd[1];

    for (int i = 0; i < GENERATORS_AMOUNT; i++) {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, generator, NULL);
        
        printf("[%ld] Launched %dth generator (thread_id = %ld)\n", pthread_self(), i+1, thread_id);
    }

    printf("[%ld] Launching number generators\n", pthread_self());
    
    int counter = 0;

    while (counter != GENERATORS_AMOUNT * GENERATED_NUMBERS_AMOUNT - 1) {
        summator_args* args = malloc(sizeof(summator_args));

        read(pipe_read_fd, &args->number1, sizeof(int));
        read(pipe_read_fd, &args->number2, sizeof(int));

        printf("[%ld] Extracted numbers from pipe on %dth iteration\n", pthread_self(), counter+1);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, summator, args);

        printf("[%ld] Launched summator (thread_id = %ld)\n", pthread_self(), thread_id);

        counter++;
    }

    printf("[%ld] Sucessfully processed all numbers\n", pthread_self());

    int result;
    read(pipe_read_fd, &result, sizeof(int));

    printf("[%ld] Extracted result from pipe\n", pthread_self());

    close(pipe_read_fd);
    close(pipe_write_fd);

    printf("[%ld] Closed pipe\n", pthread_self());

    printf("Final result: %d\n", result);
}