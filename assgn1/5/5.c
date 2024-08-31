
/*
===========================================================================================================================
Name : 5.c
Author : Hrushikesh Nakka
Description : Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd.
Date: 27th Aug, 2024.
===========================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
int arr[5] = {-1,-1,-1,-1,-1};
char filename[20];
for (int i = 1; i <= 5; ++i) 
{
  snprintf(filename, sizeof(filename), "file%d", i);
  arr[i]=open(filename, O_CREAT | O_RDONLY, 0644);
}
printf("pid: %d\n",getpid());
while(1)
{;}
return 0;
}
