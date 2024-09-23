/*
============================================================================
Name : 5f.c
Author : Hrushikesh Nakka
Description : 5. Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.
Date: 11th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int main() {
    struct sysinfo info;
    long x = sysconf(_SC_PAGESIZE);
    printf("Total number of pages in physical memory: %lu\n", info.totalram / x);
    return 0;
}
