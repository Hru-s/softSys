/*
============================================================================
Name : 29.c
Author : Hrushikesh Nakka
Description : 29. Write a program to remove the message queue.
Date: 19th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/msg.h>

int main() {
    int key = ftok(".", 3);
    int msqid = msgget(key, IPC_CREAT|0666);
    getchar();

    msgctl(msqid, IPC_RMID, NULL);

    printf("queue removed\n");

    return 0;
}

