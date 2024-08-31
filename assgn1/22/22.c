/*
===========================================================================================================================
Name : 22.c
Author : Hrushikesh Nakka
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the
            parent processes. Check output of the file.
Date: 28th Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include<fcntl.h>

int main(){
char* path = "./dummy";
int fd = open(path,O_RDWR | O_CREAT | O_TRUNC,0666);
int pid = getpid();
char buff[20];
int ipid = fork();
if(ipid==0)
{int len = snprintf(buff, sizeof(buff), "child: %d\n", getpid());
write(fd, buff, len);
}
else
{int len = snprintf(buff, sizeof(buff), "parent: %d\n", getpid());
write(fd, buff, len);
}

return 0;
}
