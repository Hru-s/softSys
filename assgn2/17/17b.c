/*
============================================================================
Name : 17b.c
Author : Hrushikesh Nakka
Description : 17. Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
Date: 16th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
  int fd[2];
  pipe(fd);
  if(fork())
  {
    close(fd[0]);
    dup2(fd[1],1);
    execlp("ls", "ls", "-l", (char*) NULL);
  }
  else
  {
    close(fd[1]);
    dup2(fd[0],0);
    execlp("wc", "wc", (char*) NULL);
  }
  return 0;
}
