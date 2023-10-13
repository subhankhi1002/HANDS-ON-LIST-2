/*
============================================================================
Name : 17a.c
Author : Subhankhi Maiti
Description : Write a program to execute ls -l | wc.
a. use dup
Date: 15th Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int fd[2];
	pipe(fd);
	if (!fork()) {
		close(1); // close STDOUT
	        close(fd[0]);
		dup(fd[1]); // Duplicate fd[1] to lowest fd value available = 1
                execlp("ls", "ls", "-l", (char*) NULL);
                // execlp() will write output of "ls -l" to fd with value = 1 (write-end of pipe)
      }
	else {
		close(0); // close STDIN
		close(fd[1]);
		dup(fd[0]); // Duplicate fd[0] to lowest fd value available = 0
                execlp("wc", "wc", (char*) NULL);
                // execlp() will read input from fd with value = 0 (read-end ofpipe) as input to “wc” command and show output to fd with value = 1 =>STDOUT
}
}
