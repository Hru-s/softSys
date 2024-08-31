/*
===========================================================================================================================
Name : 19.c
Author : Hrushikesh Nakka
Description : write a program to find out time taken to execute getpid system call. use time stamp counter.
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include <stdio.h>
#include <sys/syscall.h>
#include<stdint.h>
#include<unistd.h>

static inline uint64_t pul() {
    uint64_t lo, hi;
    __asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
int pid;    
uint64_t  before,after;
    before=pul();
    pid = syscall(SYS_getpid);
    after = pul();
    printf("PID: %d\n", pid);
    printf("Time taken : %lu\n", after-before);
    return 0;
}
