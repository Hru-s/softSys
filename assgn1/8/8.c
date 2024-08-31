/*
===========================================================================================================================
Name : 8.c
Author : Hrushikesh Nakka
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.
Date: 27th Aug, 2024.
===========================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *file;
    char buff[100];
    file = fopen("dummy", "r");
    while (fgets(buff, sizeof(buff), file) != NULL) {
    printf("%s", buff);
    }
    fclose(file);
    return 0;
}
