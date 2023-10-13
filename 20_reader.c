/*
============================================================================
Name : 20_reader.c
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
	int fd = open("myfifo", O_RDONLY);
	char buff[1024];
	read(fd, buff, sizeof(buff));
	printf("The text from FIFO file: %s\n", buff);
	getchar();
}
