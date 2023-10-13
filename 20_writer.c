/*
============================================================================
Name : 20_writer.c
Author : Subhankhi Maiti
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 22nd Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	const char *fifo_path = "myfifo"; // Name of the FIFO file
  // Check if the FIFO already exists, and if not, create it
    if (access(fifo_path, F_OK) == -1) {
        if (mkfifo(fifo_path, 0666) == -1) {
            perror("mkfifo");
            // You can choose to handle the error here or ignore it
        }
    }
	int fd = open("myfifo", O_WRONLY);
	printf("Enter the text:");
	char buff[1024];
	scanf(" %[^\n]", buff);
	write(fd, buff, sizeof(buff));
	
	
}
