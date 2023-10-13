/*
============================================================================
Name : 23.c
Author : Subhankhi Maiti
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 29th Sept, 2023.
============================================================================
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    // Get the maximum number of files that can be opened by a process
    long max_files = sysconf(_SC_OPEN_MAX);
    if (max_files == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    printf("Maximum number of files that can be opened by a process: %ld\n", max_files);

    // Create a pipe to determine the size of the pipe's circular buffer
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Determine the size of the pipe's circular buffer
    int pipe_size = fcntl(pipe_fd[0], F_GETPIPE_SZ);
    if (pipe_size == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    printf("Size of the pipe's circular buffer: %d bytes\n", pipe_size);

    // Close the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}

