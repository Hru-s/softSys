/*
============================================================================
Name : 8d.c
Author : Hrushikesh Nakka
Description : 8. Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
Date: 23th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("caught\n");
    exit(1);
}

int main() {
    signal(SIGALRM, handle_sigalrm);
    alarm(2);
    while (1) {
        pause();
    }
    return 0;
}

