/*
===========================================================================================================================
Name : 13.c
Author : Hrushikesh Nakka
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
        verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 27nd Aug, 2024.
===========================================================================================================================
*/

#include<stdio.h>
#include <sys/select.h>
int main()
{
fd_set fd;
FD_ZERO(&fd);
FD_SET(0,&fd);

struct timeval t;
t.tv_sec=10;
t.tv_usec=0;

int x= select(1,&fd,NULL, NULL,&t);
if(x==-1)
printf("error");
if(x==0)
 printf("no input recieved\n");
else
printf("input recieved\n");
return 0;}
