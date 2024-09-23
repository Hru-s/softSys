/*
============================================================================
Name : 10a.c
Author : Hrushikesh Nakka
Description : 10. Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
Date: 23th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV\n");
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigsegv;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);
    int *p = NULL;
    *p = 1;
    return 0;
}

