/*
===========================================================================================================================
Name : 9.c
Author : Hrushikesh Nakka
Description : Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change

Date: 27th Aug, 2024.
===========================================================================================================================
*/
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
char *x = "9.c";    
struct stat file_stat;
    stat(x, &file_stat);
    printf("File: %s\n", x);
    printf("Inode number: %ld\n", (long)file_stat.st_ino);
    printf("Number of hard links: %ld\n", (long)file_stat.st_nlink);
    printf("UID: %d\n", file_stat.st_uid);
    printf("GID: %d\n", file_stat.st_gid);
    printf("Size: %ld bytes\n", (long)file_stat.st_size);
    printf("Block size: %ld bytes\n", (long)file_stat.st_blksize);
    printf("Number of blocks: %ld\n", (long)file_stat.st_blocks);
    printf("Time of last access: %s", ctime(&file_stat.st_atime));
    printf("Time of last modification: %s", ctime(&file_stat.st_mtime));
    printf("Time of last status change: %s", ctime(&file_stat.st_ctime));
    return 0;
}
