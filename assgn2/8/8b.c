/*
============================================================================
Name : 8b.c
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

void handle_sigint(int sig) {
    printf("caught\n");
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);
    while (1) {
        pause();
    }
    return 0;
}


