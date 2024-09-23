/*
============================================================================
Name : 34b.c
Author : Hrushikesh Nakka
Description : 34. Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date: 21th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define PORT 3558


void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);
    char buffer[100];

    read(client_socket, buffer, sizeof(buffer));
    printf("Message from client: %s\n", buffer);
    write(client_socket, "ACK\n", 4);
    close(client_socket);
    return NULL;
}

int main() {
    int server_socket, *client_socket;
    struct sockaddr_in server_addr = {0}, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(3558);
    
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = malloc(sizeof(int));
        *client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, client_socket);
        pthread_detach(thread_id);
    }

    close(server_socket);
    return 0;
}

