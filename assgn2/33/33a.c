/*
============================================================================
Name : 33a.c
Author : Hrushikesh Nakka
Description : 33. Write a program to communicate between two machines using socket.
Date: 21th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
char buf[80];

int sd = socket(AF_UNIX, SOCK_STREAM, 0);

struct sockaddr_in serv, cli;
serv.sin_family = AF_UNIX;
serv.sin_addr.s_addr = INADDR_ANY;
serv.sin_port = htons(3558);


bind(sd, (void*) (&serv), sizeof(serv));
listen(sd, 5); 
int sz = sizeof(cli);

int nsd = accept(sd, (void*) (&cli), &sz);
read(nsd, buf, sizeof(buf));
printf("Message from client: %s\n", buf);
write(nsd, "ACK from Server\n", 17);
}
