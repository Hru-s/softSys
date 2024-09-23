/*
============================================================================
Name : 28.c
Author : Hrushikesh Nakka
Description : 28. Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 19th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/msg.h>

int main() {
    int key=ftok(".", 2);
    int msqid= msgget(key, IPC_CREAT|0666 );


    struct msqid_ds buf;
    msgctl(msqid, IPC_STAT, &buf) ;

    
    buf.msg_perm.mode = 0600;

    msgctl(msqid, IPC_SET, &buf);
    printf("permissions changed.\n");

    return 0;
}

