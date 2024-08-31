/*
============================================================================
Name : 1a.c
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
symlink("original.txt" , "csoft.txt");
return 0;}
