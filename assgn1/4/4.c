
/*
===========================================================================================================================
Name : 4.c
Author : Hrushikesh Nakka
Description : Write a program to open an existing file with read write mode.
Date: 27th Aug, 2024.
===========================================================================================================================
*/

#include<stdio.h>
#include<fcntl.h>
int main(){

int fd = open("dummy", O_CREAT | O_RDWR);
if(fd!=-1){
printf("file created without excl\n");}
if(-1==open("dummy", O_CREAT | O_EXCL | O_RDONLY ))
{printf("o_excl flag failed\n");}
return 0;}
