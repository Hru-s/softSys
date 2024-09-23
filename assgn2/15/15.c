/*
============================================================================
Name : 15.c
Author : Hrushikesh Nakka
Description : 15. Write a simple program to send some data from parent to the child process.
Date: 15th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    
    
    
    

    if(!fork())
{
        close(pipefd[1]);
        char buff2[100];
        int n = read(pipefd[0], buff2, sizeof(buff2));
        printf("read: %s\n", buff2);
        close(pipefd[0]);
    } else {

        close(pipefd[0]);

        char buff1[] = "MESSAGE";
        write(pipefd[1], buff1, sizeof(buff1));
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}

