/*
============================================================================
Name : 7.c
Author : Hrushikesh Nakka
Description : 7. Write a simple program to print the created thread ids.
Date: 22th Sep, 2024.
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
    pthread_t thread_ids[3];
    int thread_args[3];
    for (int i = 0; i < 3; i++) {
        thread_args[i] = i;
    pthread_create(&thread_ids[i], NULL, func, (void *)&thread_args[i]);}
    printf("thread ids are:\n");
    for (int i = 0; i < 3; i++) {
    printf("%d\n",thread_ids[i]);}

    return 0;
}

