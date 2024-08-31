/*
===========================================================================================================================
Name : 17b.c
Author : Hrushikesh Nakka
Description : Write a program to simulate online ticket reservation. Implement write lock
	      Write a program to open a file, store a ticket number and exit. Write a separate program, to
	      open the file, implement write lock, read the ticket number, increment the number and print
	      the new ticket number then close the file.
Date: 29th Aug, 2024.
===========================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 

int main(){

int fd = open("db", O_RDWR);
int no;
char buff[100];

struct flock lock;
lock.l_type=F_WRLCK;
lock.l_whence=SEEK_SET;
lock.l_start=0;
lock.l_len=0;

fcntl(fd,F_SETLKW,&lock);

read(fd, &buff, sizeof(buff));
no = atoi(buff);
no++;
printf("New ticket number: %d\n", no);
sprintf(buff, "%d", no);
lseek(fd, 0, SEEK_SET);
write(fd, &buff, sizeof(buff));


lock.l_type=F_UNLCK;
fcntl(fd,F_SETLK,&lock);

close(fd);

return 0;
}


