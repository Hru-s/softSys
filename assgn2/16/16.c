/*
============================================================================
Name : 16.c
Author : Hrushikesh Nakka
Description : 16. Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 15th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

char buff1[100],buff2[100];
int fd1[2];
int fd2[2];
pipe(fd1);
pipe(fd2);
if (fork()) {
close(fd1[1]); 
close(fd2[0]); 
read(fd1[0], buff1, sizeof(buff1));
printf("Message from child: %s\n", buff1);
printf("Enter message to child: ");
scanf(" %[^\n]", buff2);
write(fd2[1], buff2, sizeof(buff2));
}
else {
close(fd1[0]); 
close(fd2[1]); 
printf("Enter message to parent: ");
scanf(" %[^\n]", buff1);
write(fd1[1], buff1, sizeof(buff1));
read(fd2[0], buff2, sizeof(buff2));
printf("Message from parent: %s\n", buff2);
}
return 0;
}
