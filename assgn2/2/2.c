/*
============================================================================
Name : 2.c
Author : Hrushikesh Nakka
Description : 2. Write a program to print the system resource limits. Use getrlimit system call.
Date: 10th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <limits.h>

void print_resource_limit(int resource) {
  struct rlimit l;
  getrlimit(resource, &l);

    printf("Resource: %d\n", resource);
  printf("Soft limit: %ld\n", l.rlim_cur);
    printf("Hard limit: %ld\n", l.rlim_max);
    printf("\n");}

void main() {
    print_resource_limit(RLIMIT_CPU);
    print_resource_limit(RLIMIT_FSIZE);
    print_resource_limit(RLIMIT_DATA);
    print_resource_limit(RLIMIT_STACK);
    print_resource_limit(RLIMIT_CORE);
    print_resource_limit(RLIMIT_RSS);
    print_resource_limit(RLIMIT_NPROC);
    print_resource_limit(RLIMIT_NOFILE);
    print_resource_limit(RLIMIT_MEMLOCK);
    print_resource_limit(RLIMIT_AS);
    print_resource_limit(RLIMIT_LOCKS);
    print_resource_limit(RLIMIT_SIGPENDING);
    print_resource_limit(RLIMIT_MSGQUEUE);
    print_resource_limit(RLIMIT_NICE);
    print_resource_limit(RLIMIT_RTPRIO);
    print_resource_limit(RLIMIT_RTTIME);

}

