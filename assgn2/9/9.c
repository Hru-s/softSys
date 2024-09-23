/*
============================================================================
Name : 9.c
Author : Hrushikesh Nakka
Description : 9. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 23th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void lol(int sig) {
    printf("SIGINT received and ignored.\n");
}

int main() {
    signal(SIGINT, lol);

    printf("Ignoring SIGINT.\n");
    sleep(5);

    signal(SIGINT, SIG_DFL);
    printf("SIGINT is reset\n");
    sleep(5);

    return 0;
}

