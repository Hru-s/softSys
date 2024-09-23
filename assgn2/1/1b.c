/*
============================================================================
Name : 1b.c
Author : Hrushikesh Nakka
Description : 1. Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF
Date: 10th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int signum) {
    printf("timer expired\n");}

int main() {
    struct itimerval timer;

    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 10;       
    timer.it_value.tv_usec = 10;      
    timer.it_interval.tv_sec = 0;     
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    int i=0;
    while (1) {
        i++;
    }

    return 0;
}

