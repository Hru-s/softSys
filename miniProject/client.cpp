#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main() {
    struct sockaddr_in serv;
    int sd;
    char buf[1000]; // Increased buffer size for larger messages
    char userInput[80]; // Buffer to hold user input

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Failed to create socket");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY); // Use the server's IP address
    serv.sin_port = htons(8081); // Specify port

    // Connect client socket to server
    if (connect(sd, (struct sockaddr*)(&serv), sizeof(serv)) < 0) {
        perror("Connection failed");
        close(sd);
        return 1;
    }

    while (true) {
        memset(buf, 0, sizeof(buf)); // Clear the buffer before reading

        // Read response from server
        ssize_t bytesRead = read(sd, buf, sizeof(buf)); // Leave space for null terminator
        if (bytesRead < 0) {
            perror("Read failed");
            break; // Exit loop on error
        } else if (bytesRead == 0) {
            cout << "Server closed the connection." << endl;
            break; // Exit loop if server closes the connection
        }

        buf[bytesRead] = '\0'; // Null-terminate the string
        cout << "Message from server: " << buf; // Display the server message

        // Prompt for user input
        cout << "Enter your reply: \n";
        string msg;
        cin >> msg; // Read user input

        // Send user input to server
        int bytesSent = write(sd, msg.c_str(), msg.size());
        if (bytesSent < 0) {
            perror("Failed to send message");
            break; // Exit loop on error
        }
        cout<<"bytes sent from client: "<<bytesSent<<endl;
    }

    // Close the socket
    close(sd);
    return 0;
}
