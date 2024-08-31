/*
===========================================================================================================================
Name : 15.c
Author : Hrushikesh Nakka
Description : Write a program to display the environmental variable of the user (use environ).
Date: 27nd Aug, 2024.
===========================================================================================================================
*/
#include <stdio.h>
extern char** environ;
int main(void) {
  for (int i = 0; environ[i] != NULL; i++) {
    printf("%s\n", environ[i]);
  }
  return 0;
}
