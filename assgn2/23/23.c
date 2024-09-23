/*
============================================================================
Name : 23.c
Author : Hrushikesh Nakka
Description : 23. Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 18th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit limit;
    getrlimit(RLIMIT_NOFILE, &limit);
    int pipe_size = fpathconf(STDIN_FILENO, _PC_PIPE_BUF);
    printf("Maximum number of open files:\n Soft limit: %lu, Hard limit: %lu\n", limit.rlim_cur, limit.rlim_max);    
    printf("Size of pipe (circular buffer): %d bytes\n", pipe_size);
    return 0;
}

