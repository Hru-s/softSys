/*
============================================================================
Name : 19d.c
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
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    mkfifo("my_fifo", 0666);
    printf("FIFO created with mkfifo.\n");
    return 0;
}

