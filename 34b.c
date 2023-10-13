/*
============================================================================
Name : 34b.c
Author : Subhankhi Maiti
Description : Write a program to create a concurrent server.
b. use pthread_create
Date: 13th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERVER_PORT 8080
#define MAX_BUFFER_SIZE 1024

// Function to handle client requests in a separate thread
void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[MAX_BUFFER_SIZE];

    // Receive a message from the client
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("Read failed");
        close(client_socket);
        pthread_exit(NULL);
    }

    buffer[bytes_received] = '\0'; // Null-terminate the received data
    printf("Received from client: %s\n", buffer);

    // Send a response back to the client
    const char *response = "Hello from server!";
    send(client_socket, response, strlen(response), 0);

    // Close the client socket and exit the thread
    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        // Accept an incoming connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Acceptance failed");
            continue; // Continue to the next iteration
        }

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, &client_socket) != 0) {
            perror("Thread creation failed");
            close(client_socket);
        }
    }

    // Close the server socket (never reached in this example)
    close(server_socket);

    return 0;
}

