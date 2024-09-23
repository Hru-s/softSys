/*
============================================================================
Name : 19c.c
Author : Hrushikesh Nakka
Description : 19. Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 16th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    mknod("my_fifo", S_IFIFO | 0666, 0);
    printf("FIFO created with mknod.\n");
    return 0;
}

