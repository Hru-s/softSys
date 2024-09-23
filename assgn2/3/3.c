/*
============================================================================
Name : 3.c
Author : Hrushikesh Nakka
Description : 3. Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 10th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <limits.h>

int main() {
    struct rlimit l;

    l.rlim_cur = 5 * 1024 * 1024;
    l.rlim_max = 7 * 1024 * 1024;

    setrlimit(RLIMIT_MSGQUEUE, &l);

    printf("msq limit changed.\n");

    return 0;
}
