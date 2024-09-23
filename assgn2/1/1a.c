/*
============================================================================
Name : 1a.c
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

int main() {
    struct itimerval timer;
    timer.it_value.tv_sec = 10;          
    timer.it_value.tv_usec = 10;          
    timer.it_interval.tv_sec = 0;        
    timer.it_interval.tv_usec = 0;  
        setitimer(ITIMER_REAL, &timer, NULL);
        while (1) {
        pause(); 
    }
    }
