/*
============================================================================
Name : 15.c
Author : Subhankhi Maiti
Description : Write a simple program to send some data from parent to the child process.
Date: 15th Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2]; // File descriptors for the pipe
    pid_t child_pid; // PID of the child process

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(pipe_fd[1]); // Close the write end of the pipe in the child process

        char buffer[256];
        ssize_t read_bytes;

        // Read from the pipe and display on the monitor
        read_bytes = read(pipe_fd[0], buffer, sizeof(buffer));

        if (read_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Child received: %s", buffer);

        close(pipe_fd[0]); // Close the read end of the pipe in the child process
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe in the parent process

        char *message = "Hello, child process!\n";
        ssize_t written_bytes;

        // Write to the pipe
        written_bytes = write(pipe_fd[1], message, strlen(message));

        if (written_bytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]); // Close the write end of the pipe in the parent process
    }

    return 0;
}

