/*
============================================================================
Name : 32c.c
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

#define NUM_RESOURCES 2
#define NUM_THREADS 5

sem_t resource_semaphore;

void *use_resources(void *arg) {
    int thread_id = *(int *)arg;

    sem_wait(&resource_semaphore);
    printf("Thread %d accessing resource\n", thread_id);
    sleep(2);
    printf("Thread %d releasing resource\n", thread_id);
    sem_post(&resource_semaphore);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    sem_init(&resource_semaphore, 0, NUM_RESOURCES);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, use_resources, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&resource_semaphore);
    return 0;
}

