/*
============================================================================
Name : 1c.c
Author : Hrushikesh Nakka
Description : Create the following types of files using i)shell command ii)system call
              a.soft link (symlink system call)
              b.hard link
              c.FIFO
Date: 27th Aug, 2024.
============================================================================
*/
#include <sys/stat.h>
#include<unistd.h>
int main(){
mkfifo("cpipe" , 0666);
return 0;}
