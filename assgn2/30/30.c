/*
============================================================================
Name : 30.c
Author : Hrushikesh Nakka
Description : 30. Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 19th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key = ftok(".", 'R');
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    
    char *data = (char *)shmat(shmid, NULL, 0);
    strcpy(data, "Hello, Shared Memory!");
    printf("Written to shared memory: %s\n", data);

    shmdt(data);
    
    data = (char *)shmat(shmid, NULL, SHM_RDONLY);
    printf("Trying to overwrite in read-only mode...\n");
    strcpy(data, "This should not work!"); 
    printf("Read from shared memory: %s\n", data);

    shmdt(data);
    
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}

