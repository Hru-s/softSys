/*
===========================================================================================================================
Name : 23.c
Author : Hrushikesh Nakka
Description : Write a program to create a Zombie state of the running program.
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
int pid = fork();
if (pid == 0) {
sleep(1);
printf("Child terminated\n");
exit(0);
} 
else {
	printf("parent sleeping\n");
	sleep(10);
	printf("parent woke up\n");
}

return 0;
}
