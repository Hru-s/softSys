/*
===========================================================================================================================
Name : 21.c
Author : Hrushikesh Nakka
Description : Write a program, call fork and print the parent and child process id.
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
int main(){
int pid = fork();
if(pid!=0)
{printf("child: %d",pid);
printf("\nparent: %d\n",getpid());
}return 0;
}
