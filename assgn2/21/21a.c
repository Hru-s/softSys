/*
============================================================================
Name : 21a.c
Author : Hrushikesh Nakka
Description : 21. Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 17th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

    char buff[] = "msg from a";
    char buff1[20];
    mkfifo("f1", 0666);



    int fd = open("f1", O_WRONLY);

    write(fd, buff, sizeof(buff));
    int fd1 = open("f2", O_RDONLY);
    read(fd1,buff1,sizeof(buff1));
    printf("received: %s\n", buff1);

    return 0;
}
