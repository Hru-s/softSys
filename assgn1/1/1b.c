/*
============================================================================
Name : 1b.c
Author : Hrushikesh Nakka
Description : Create the following types of files using i)shell command ii)system call
              a.soft link (symlink system call)
              b.hard link
              c.FIFO
Date: 27th Aug, 2024.
============================================================================
*/
#include<unistd.h>
int main(){
link("original.txt" , "chard.txt");
return 0;}
