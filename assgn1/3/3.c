/*
===========================================================================================================================
Name : 3.c
Author : Hrushikesh Nakka
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call.
Date: 27th Aug, 2024.
===========================================================================================================================
*/
#include <fcntl.h>
#include <stdio.h>
int main(){

int fd = creat("example.txt",0644);

printf("fd: %d\n",fd);
return 0;
}
