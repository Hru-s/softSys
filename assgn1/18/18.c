/*
===========================================================================================================================
Name : 18.c
Author : Hrushikesh Nakka
Description : Write a program to perform Record locking.
        a. Implement write lock
        b. Implement read lock
        Create three records in a file. Whenever you access a particular record, first lock it then modify/access
        to avoid race condition.
Date: 29th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include <unistd.h> 

int main(){
int fd1 = open("file1", O_CREAT | O_RDWR, 0666);
int fd2 = open("file2", O_CREAT | O_RDWR, 0666);
int fd3 = open("file3", O_CREAT | O_RDWR, 0666);
char buff[100]="hello";

struct flock lock;
lock.l_type = F_WRLCK; 
lock.l_whence = SEEK_SET; 
lock.l_start = 0;
lock.l_len = 0; 
fcntl(fd1,F_SETLKW,&lock);

printf("critical");
write(fd1, buff, sizeof(buff));

lock.l_type=F_UNLCK;
fcntl(fd1,F_SETLK,&lock);

lock.l_type = F_WRLCK;
fcntl(fd1,F_SETLKW,&lock);
read(fd1,&buff,sizeof(buff));
getchar();
lock.l_type=F_UNLCK;
fcntl(fd1,F_SETLK,&lock);

return 0;
}
