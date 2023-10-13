/*
============================================================================
Name : 19c.c
Author : Subhankhi Maiti
Description : Create a FIFO file by
c. mknod system call
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

    // Create a FIFO file using the mknod system call
    if (mknod(fifo_path, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }

    printf("FIFO file '%s' created successfully.\n", fifo_path);

    return 0;
}

