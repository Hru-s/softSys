/*
============================================================================
Name : 13a.c
Author : Hrushikesh Nakka
Description : 13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 14th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigstop(int sig) {
    printf("Caught SIGSTOP\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigstop;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSTOP, &sa, NULL);
    
    printf("Waiting to catch SIGSTOP, pid:%d\n",getpid());
    while (1) {
        pause(); 
    }

    return 0;
}

