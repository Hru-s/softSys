/*
============================================================================
Name : 20a.c
Author : Hrushikesh Nakka
Description : 20. Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 17th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

    char buff[] = "msg";
    mkfifo("f", 0666);



    int fd = open("f", O_WRONLY);

    write(fd, buff, sizeof(buff));

    printf("sent: %s\n", buff);

    return 0;
}
