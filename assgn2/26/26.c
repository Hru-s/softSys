/*
============================================================================
Name : 26.c
Author : Hrushikesh Nakka
Description : 26. Write a program to send messages to the message queue. Check $ipcs -q
Date: 19th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/msg.h>
int main() {

int key = ftok(".", 3);
int msqid = msgget(key, IPC_CREAT|0744);
printf("key=%d\t msgid=%d\n", key, msqid);

struct msg {
long int m_type;
char message[80];
} myq;

printf("Enter message type: ");
scanf("%ld", &myq.m_type);
printf("Enter message text:\n");
scanf(" %[^\n]", myq.message);
int size = sizeof(myq.message);
msgsnd(msqid, &myq, size + 1, 0);
}
