/*
===========================================================================================================================
Name : 25.c
Author : Hrushikesh Nakka
Description : Write a program to create three child processes. The parent should wait for a particular child    
        (use waitpid system call).
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
int list[3]={-1,-1,-1};
int pid=getpid();
for(int i=0;i<3;i++)
{
	if(getpid()==pid)
	list[i]=fork();
}

if(getpid()==pid)
{	printf("parent waiting\n");
	int status;
	waitpid(list[2],&status,0);
	printf("parent finished waiting\n");}
if(0==list[2])
	{sleep(5);
printf("child woke\n");}
	return 0;}
