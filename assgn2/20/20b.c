/*
============================================================================
Name : 20b.c
Author : Hrushikesh Nakka
Description : 20. Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 17th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buff[100];

    int fd = open("f", O_RDONLY);

    int n = read(fd, buff, sizeof(buff));

    printf("received: %s\n", buff);

    return 0;
}

