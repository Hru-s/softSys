/*
===========================================================================================================================
Name : 27a.c
Author : Hrushikesh Nakka
Description : Write a program to execute ls -Rl by the following system calls
            a. execl
            b. execlp
            c. execled
            d. execv
            e. execvp
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include <unistd.h> 

int main(){
int error = execl("/usr/bin/ls", "ls", "-Rl", NULL);

return 0;}
