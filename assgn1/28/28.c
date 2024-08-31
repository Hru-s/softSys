/*
===========================================================================================================================
Name : 28.c
Author : Hrushikesh Nakka
Description : Write a program to get maximum and minimum real time priority.
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    int fifomax = sched_get_priority_max(SCHED_FIFO);
    int fifomin = sched_get_priority_min(SCHED_FIFO);

    int rrmax = sched_get_priority_max(SCHED_RR);
    int rrmin = sched_get_priority_min(SCHED_RR);
    printf("SCHED_FIFO:\n  Maximum priority: %d\n", fifomax);
    printf("  Minimum priority: %d\n", fifomin);
    printf("SCHED RR:\n  Maximum priority: %d\n", rrmax);
    printf("  Minimum priority: %d\n", rrmin);

    return 0;
}
