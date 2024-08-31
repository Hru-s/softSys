/*
===========================================================================================================================
Name : 30.c
Author : Hrushikesh Nakka
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 30th Aug, 2024.
===========================================================================================================================
*/

#include<unistd.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    if(!fork()){
      setsid();
      chdir("/");
      while(1){
        sleep(2);
        printf("Hi, im Daemon\n");
      }
    }
    else    
       { exit(0);}
    return 0;
}
