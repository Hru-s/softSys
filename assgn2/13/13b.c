/*
============================================================================
Name : 13b.c
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

int main() {
    int pid;
    printf("enter pid to kill\n");
    scanf("%d",&pid);
    kill(pid, SIGSTOP);
    printf("SIGSTOP sent to process \n");

    return 0;
}

