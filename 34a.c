/*
============================================================================
Name : 34a.c
Author : Subhankhi Maiti
Description : Write a program to create a concurrent server.
a. use fork
Date: 13th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CLIENTS 5

void handle_client(int client_socket) {
    char buffer[1024];
    int bytes_received;

    // Read data from the client
    bytes_received = read(client_socket, buffer, sizeof(buffer));
    if (bytes_received < 0) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }

    printf("Received: %s\n", buffer);

    // Process client data (you can implement your own logic here)

    // Send a response to the client
    const char *response = "Hello from server!";
    write(client_socket, response, strlen(response));

    // Close the client socket
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept an incoming connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Acceptance failed");
            exit(EXIT_FAILURE);
        }

        // Create a child process to handle the client
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            // This is the child process
            close(server_socket); // Close the server socket in the child
            handle_client(client_socket);
            exit(0);
        } else {
            // This is the parent process
            close(client_socket); // Close the client socket in the parent
        }
    }

    return 0;
}

