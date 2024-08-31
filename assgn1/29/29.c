/*
===========================================================================================================================
Name : 29.c
Author : Hrushikesh Nakka
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,
SCHED_RR).
Date: 30th Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

void display(int p) {
    switch (p) {
        case SCHED_FIFO:
            printf("Curre. policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Curr. policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Curr. policy: SCHED_OTHER\n");
            break;
        default:
            printf("Curr. policy: Unknown\n");
            break;
    }
}

int main() {
    int currp;
    struct sched_param param;
    currp = sched_getscheduler(getpid());
    display(currp);
    param.sched_priority = 5; 

    sched_setscheduler(getpid(), SCHED_FIFO, &param);
    printf("Changed scheduling policy to SCHED_FIFO\n");
    currp = sched_getscheduler(getpid());
    display(currp);

    sched_setscheduler(getpid(), SCHED_RR, &param);
    printf("Changed scheduling policy to SCHED_RR\n");
    currp = sched_getscheduler(getpid());
    display(currp);
    return 0;
}
