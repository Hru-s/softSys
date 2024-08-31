/*
===========================================================================================================================
Name : 10.c
Author : Hrushikesh Nakka
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
    a. check the return value of lseek.
    b. open the file with od and check the empty spaces in between the data.

Date: 27th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
char buff[20]="1234567890";
int fd = open("example.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
write(fd, buff, 10);
lseek(fd,10,SEEK_CUR);
write(fd, buff, 10);
return 0;}
