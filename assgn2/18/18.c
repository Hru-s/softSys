/*
============================================================================
Name : 18.c
Author : Hrushikesh Nakka
Description : 18. Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 16th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
  int fd[2],fd1[2];
  pipe(fd);
  pipe(fd1);
  if(fork())
  {
    if(fork())
    {
    close(fd[0]);
    close(fd1[0]);
    close(fd1[1]);
    dup2(fd[1],1);
    execlp("ls", "ls", "-l", (char*) NULL);
    }
    else
    {
      close(fd[1]);
      close(fd1[0]);
      dup2(fd[0],0);
      dup2(fd1[1],1);
      execlp("grep", "grep", "^d", (char*) NULL);
    }
  }
  else
  {
    close(fd[1]);
    close(fd[0]);
    close(fd1[1]);
    dup2(fd1[0],0);
    execlp("wc", "wc", (char*) NULL);
  }
  return 0;
}
