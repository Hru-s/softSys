/*
============================================================================
Name : 31b.c
Author : Hrushikesh Nakka
Description : 31. Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {

    int key = ftok(".", 2);

    int semid = semget(key, 1, IPC_CREAT | 0666);
    
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = 10;
    sem_op.sem_flg = 0;
    
    semop(semid, &sem_op, 1);
    
    return 0;
    }
