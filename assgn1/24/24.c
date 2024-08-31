/*
===========================================================================================================================
Name : 24.c
Author : Hrushikesh Nakka
Description : Write a program to create an orphan process.
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process: %d started\n", getpid());
        sleep(5);
        printf("Child process: %d is now orphan\n", getpid());
        exit(0);
    } else {
        printf("Parent process terminated\n");
        exit(0);
    }

    return 0;
}
