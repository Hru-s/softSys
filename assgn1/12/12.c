/*
===========================================================================================================================
Name : 12.c
Author : Hrushikesh Nakka
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 27nd Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>

void filecheck(int flags) {

    printf("File mode:\n %d\n",flags);

    if ((flags & O_ACCMODE) == O_RDONLY) printf("Opened in Read-only\n");
    if ((flags & O_ACCMODE)==O_WRONLY ) printf("Opened in Write-only\n");
    if ((flags & O_ACCMODE)==O_RDWR)   printf("Opened in Read and Write\n");
    
}

int main()
{
int fd =open("file12" , O_CREAT | O_TRUNC | O_RDONLY,0666 );
int flags=fcntl(fd,F_GETFL);
filecheck(flags);
return 0;
}
