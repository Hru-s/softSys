/*Name : 11.c
Author : Hrushikesh Nakka
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the
        descriptors and check whether the file is updated properly or not.
        a. use dup
        b. use dup2
        c. use fcntl
Date: 27nd Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){

int fd = open("file11" , O_CREAT | O_TRUNC| O_RDWR, 0666);
int fd1;
int c;
printf("choose:\n");
printf("1.dup\n");
printf("2.dup2:\n");
printf("3.fcntl:\n");
printf("enter corresponding int:\n");
scanf("%d",&c);
if(c==1)
{fd1 = dup(fd);}
if(c==2)
{fd1 = dup2(fd,4);}
if(c==3)
{fd1=fcntl(fd,F_DUPFD,15);}
printf("fd: %d\n",fd1);
close(fd);
close(fd1);
return 0;}
