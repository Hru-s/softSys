/*
===========================================================================================================================
Name : 17a.c
Author : Hrushikesh Nakka
Description : Write a program to simulate online ticket reservation. Implement write lock
	      Write a program to open a file, store a ticket number and exit. Write a separate program, to
	      open the file, implement write lock, read the ticket number, increment the number and print
	      the new ticket number then close the file.
Date: 29th Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 

int main(){

int fd = open("db", O_RDWR | O_CREAT, 0666);
char buff[100]="0";
write(fd, &buff, sizeof(buff));


return 0;
}





