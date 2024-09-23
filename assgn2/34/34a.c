/*
============================================================================
Name : 34a.c
Author : Hrushikesh Nakka
Description : 34. Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date: 21th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>



void handle_client(int client_socket) {
    char buffer[80];

    read(client_socket, buffer, sizeof(buffer));
    printf("Message from client: %s\n", buffer);
    write(client_socket, "ACK\n", 4);
    close(client_socket);
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr = {0}, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    printf("Server listening on port %d\n", 8080);

    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            continue; 
        }

        if (fork() == 0) {
          
            close(server_socket); 
            handle_client(client_socket);
            exit(0);
        }
        close(client_socket); 
    }

    close(server_socket);
    return 0;
}

