/*
============================================================================
Name : 8a.c
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

void handle_sigsegv(int sig) {
printf("caught\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, handle_sigsegv);
    int *p = NULL;
    *p = 42;
    return 0;
}

