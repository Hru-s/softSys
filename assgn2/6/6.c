/*
============================================================================
Name : 6.c
Author : Hrushikesh Nakka
Description : 6. Write a simple program to create three threads.
Date: 11th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *func(void *arg) {
    int thread_num = *((int *)arg);
    printf("Hello from thread %d\n", thread_num);
    pthread_exit(NULL);
}

int main() {
    int thread_ids[3];
    int thread_args[3];
    for (int i = 0; i < 3; i++) {
        thread_args[i] = i;
        pthread_create((pthread_t *)&thread_ids[i], NULL, func, (void *)&thread_args[i]);}
    printf("done\n");

    return 0;
}

