/*
============================================================================
Name : 27a.c
Author : Hrushikesh Nakka
Description : 27. Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 19th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/msg.h>

int main() {
    struct msg {
    long int m_type;
    char message[80];
    } myq;
    int key = ftok(".", 3);
    int mqid = msgget(key, 0);
    printf("Enter message type: ");
    scanf("%ld", &myq.m_type);
    int ret = msgrcv(mqid, &myq, sizeof(myq.message), myq.m_type,
    IPC_NOWAIT);
    if (ret == -1)
    exit(-1);
    printf("Message type: %ld\n Message: %s\n", myq.m_type, myq.message);
}
