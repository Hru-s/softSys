/*
============================================================================
Name : 12.c
Author : Hrushikesh Nakka
Description : 12. Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 23th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {

    if (fork()) {
        printf("Parent sleeping\n");
        sleep(5);
        printf("Parent exiting\n");
        exit(0);
    } else {
        sleep(1);
        kill(getppid(), SIGKILL);
        //printf("parent killed\n");
    }

    return 0;
}

