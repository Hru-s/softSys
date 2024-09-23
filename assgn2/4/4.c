/*
============================================================================
Name : 4.c
Author : Hrushikesh Nakka
Description : 4. Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 11th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

static inline uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    int pid;
    uint64_t start = rdtsc();

    for (int i = 0; i < 100; i++) {
        pid = getppid();
    }

    uint64_t end = rdtsc();
    int elapsed = end - start;

    printf("Time taken for 100 getppid(): %d\n", elapsed);

    return 0;
}
