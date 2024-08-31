/*
===========================================================================================================================
Name : 2.c
Author : Hrushikesh Nakka
Description : Write a simple program to execute in an infinite loop at the background. Go to /proc directory and
identify all the process related information in the corresponding proc directory.
Date: 27th Aug, 2024.
===========================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
int main(){
printf("pid: %d\n",getpid());

while(1){}
return 0;}
