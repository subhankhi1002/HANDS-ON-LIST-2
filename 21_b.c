/*
============================================================================
Name : 21_b.c
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

        int fd1 = open("myfifo1", O_WRONLY);
        int fd2 = open("myfifo2", O_RDONLY);
        printf("Enter the text:");
        char buff1[1024];
        char buff2[1024];
        read(fd1, buff2, sizeof(buff2));
	scanf(" %[^\n]", buff1);

	write(fd2, buff1, sizeof(buff1));

        printf("The text from FIFO file: %s\n", buff1);
}
