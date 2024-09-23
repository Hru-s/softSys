/*
============================================================================
Name : 22.c
Author : Hrushikesh Nakka
Description : 22. Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 17th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

    char buff[12];
    mkfifo("f", 0666);
    
    fd_set fds;
    struct timeval timer;
    timer.tv_sec = 5;
    timer.tv_usec = 0;
    FD_ZERO(&fds);
    int fd = open("f", O_RDONLY|O_NONBLOCK);
    FD_SET(fd, &fds);
    if (!select(fd + 1, &fds, NULL, NULL, &timer))
    {printf("No data is available for reading yet\n");}
    else
    {
      printf("here");
      read(fd, buff, sizeof(buff));
      printf("sent: %s\n", buff);
    }
    return 0;
}
