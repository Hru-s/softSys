/*
===========================================================================================================================
Name : 26.c
Author : Hrushikesh Nakka
Description : Write a program to execute an executable program.
        a. use some executable program
        b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
int main(int argc, char *argv[]){
char *arr[3] ={"./ex",argv[1], NULL};
execvp("./ex",arr);
return 0;}
