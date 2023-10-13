/*
============================================================================
Name : 21_a.c
Author : Subhankhi Maiti
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 29th Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	if (mkfifo("myfifo1", 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
	}

	if (mkfifo("myfifo2", 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
	}



	int fd1 = open("myfifo1", O_WRONLY);
	int fd2 = open("myfifo2", O_RDONLY);
	printf("Enter the text:");
	char buff1[1024];
	char buff2[1024];
	scanf(" %[^\n]", buff1);
	write(fd1, buff1, sizeof(buff1));
	read(fd2, buff2, sizeof(buff2));
	printf("The text from FIFO file: %s\n", buff2);
}
