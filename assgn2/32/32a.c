/*
============================================================================
Name : 32a.c
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
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

int main() {
    int fd = open("db", O_RDWR);
    int key = ftok(".", 1);
    int semid = semget(key, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1);

    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;

    semop(semid, &sem_op, 1);

    char buff[100];
    read(fd, buff, sizeof(buff));
    int ticket_number = atoi(buff);
    ticket_number++;
    printf("New ticket number: %d\n", ticket_number);
    fflush(stdout);
    sprintf(buff, "%d", ticket_number);
    lseek(fd, 0, SEEK_SET);
    write(fd, buff, sizeof(buff));

    sem_op.sem_op = 1;
    semop(semid, &sem_op, 1);

    close(fd);
    return 0;
}

