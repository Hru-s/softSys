/*
============================================================================
Name : 1c.c
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
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

void func(int signum) {
    printf("timer expired\n");
}

int main() {
    struct itimerval timer;
    struct sigaction sa;
    
    sa.sa_handler = func;
    sa.sa_flags = 0; 
    sigemptyset(&sa.sa_mask); 
    sigaction(SIGPROF, &sa, NULL); 

    timer.it_value.tv_sec = 10;          
    timer.it_value.tv_usec = 10;          
    timer.it_interval.tv_sec = 0;        
    timer.it_interval.tv_usec = 0;       

    setitimer(ITIMER_PROF, &timer, NULL);
    while (1) {
        pause;}

    return 0;
}
