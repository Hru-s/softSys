/*
============================================================================
Name : 10c.c
Author : Hrushikesh Nakka
Description : 10. Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
Date: 23th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigfpe(int sig) { 
printf("caught SIGFPE\n");
exit(1);
}
int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigfpe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGFPE, &sa, NULL);
    int x = 0;
    int y = 1;
    int result = y / x;

    return 0;
}

