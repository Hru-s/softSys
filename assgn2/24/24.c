/*
============================================================================
Name : 24.c
Author : Hrushikesh Nakka
Description : 24. Write a program to create a message queue and print the key and message queue id
Date: 19th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/msg.h>
int main() {

int key = ftok(".", 3);
int msgid = msgget(key, IPC_CREAT|0744);
printf("key=%d\t msgid=%d\n", key, msgid);
}
