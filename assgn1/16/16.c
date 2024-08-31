/*
===========================================================================================================================
Name : 16.c
Author : Hrushikesh Nakka
Description : Write a program to perform mandatory locking.
        a. Implement write lock
        b. Implement read lock
Date: 29th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>

int main(){

struct flock lock;
lock.l_type=F_RDLCK;
lock.l_whence=SEEK_SET;
lock.l_start=0;
lock.l_len=0;
int fd = open("testfile.txt" , O_CREAT | O_RDWR);

fcntl(fd,F_SETLKW,&lock);

lock.l_type=F_UNLCK;
fcntl(fd,F_SETLKW,&lock);

lock.l_type=F_WRLCK;
fcntl(fd,F_SETLKW,&lock);
printf("lock acquired\n");
return 0;
}
