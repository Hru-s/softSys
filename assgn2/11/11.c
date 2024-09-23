/*
============================================================================
Name : 11.c
Author : Hrushikesh Nakka
Description : 11. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 23th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void func(int sig) {
    printf("SIGINT received and ignored.\n");
}

int main() {
    struct sigaction sa;

    sa.sa_handler = func;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    
    printf("Ignoring SIGINT. Press Ctrl+C to test.\n");
    sleep(5); 

    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT is now reset Press Ctrl+C to exit.\n");
    sleep(5);

    return 0;
}

