/*
============================================================================
Name : 32b.c
Author : Hrushikesh Nakka
Description : 32. Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date: 21th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t shared_data_semaphore;
int shared_value = 0;

void *update_shared_value(void *arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&shared_data_semaphore);
        shared_value++;
        printf("Shared Value Updated: %d\n", shared_value);
        sem_post(&shared_data_semaphore);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread_one, thread_two;

    sem_init(&shared_data_semaphore, 0, 1);

    pthread_create(&thread_one, NULL, update_shared_value, NULL);
    pthread_create(&thread_two, NULL, update_shared_value, NULL);

    pthread_join(thread_one, NULL);
    pthread_join(thread_two, NULL);

    sem_destroy(&shared_data_semaphore);
    return 0;
}

