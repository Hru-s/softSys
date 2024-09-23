/*
============================================================================
Name : 25.c
Author : Hrushikesh Nakka
Description : 25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 19th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/msg.h>
int main() {

    int key = ftok(".", 3);
    int msgid = msgget(key, IPC_CREAT|0744);



    struct msqid_ds buf;

    msgctl(msgid, IPC_STAT, &buf);


    printf("Access Permissions: %o\n", buf.msg_perm.mode);
    
    printf("Owner UID: %u\n", buf.msg_perm.uid);
    printf("Owner GID: %u\n", buf.msg_perm.gid);
    
    printf("Last Message Sent: %ld\n", buf.msg_stime);
    printf("Last Message Received: %ld\n", buf.msg_rtime);
    
    printf("Last Change Time: %ld\n", buf.msg_ctime);
    
    printf("Size of the Queue: %zu bytes\n", buf.__msg_cbytes);
    
    printf("Number of Messages: %lu\n", buf.msg_qnum);

    printf("Maximum Bytes Allowed: %lu\n", buf.msg_qbytes);
    
    printf("PID of msgsnd: %d\n", buf.msg_lspid);
    printf("PID of msgrcv: %d\n", buf.msg_lrpid);
    return 0;
}
