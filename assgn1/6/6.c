
/*
===========================================================================================================================
Name : 6.c
Author : Hrushikesh Nakka
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls.
Date: 27th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main() {
char buff[100];
int p;
p = read(0, buff, sizeof(buff));
write(1, buff, p);
return 0;
}
