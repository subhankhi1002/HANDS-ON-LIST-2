/*
============================================================================
Name : 19d.c
Author : Subhankhi Maiti
Description : Create a FIFO file by
c. mkfifo library function
Date: 22nd Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *fifo_path = "my_fifo"; // Name of the FIFO file

    // Create a FIFO file using the mkfifo library function
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("FIFO file '%s' created successfully.\n", fifo_path);

    return 0;
}

