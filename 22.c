/*
============================================================================
Name : 22.c
Author : Subhankhi Maiti
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 29th Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "myfifo"; // Name of the FIFO file
    int fd;
    if (access(fifo_path, F_OK) == -1) {
        if (mkfifo(fifo_path, 0666) == -1) {
            perror("mkfifo");
        }
    }
    // Open the FIFO for reading
    fd = open(fifo_path, O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_set read_set;
    struct timeval timeout;

    // Initialize the file descriptor set and timeout
    FD_ZERO(&read_set);
    FD_SET(fd, &read_set);
    timeout.tv_sec = 10; // 10 seconds
    timeout.tv_usec = 0;

    printf("Waiting for data in the FIFO...\n");

    // Use select to wait for data or a timeout
    int result = select(fd + 1, &read_set, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (result == 0) {
        printf("Timeout: No data received within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &read_set)) {
            char buffer[256];
            ssize_t bytes_read;

            // Read data from the FIFO
            bytes_read = read(fd, buffer, sizeof(buffer));

            if (bytes_read == -1) {
                perror("read");
                close(fd);
                exit(EXIT_FAILURE);
            }

            printf("Data received from the FIFO: %.*s\n", (int)bytes_read, buffer);
        }
    }

    // Close the FIFO
    close(fd);

    return 0;
}

