/*
============================================================================
Name : 17b.c
Author : Subhankhi Maiti
Description : Write a program to execute ls -l | wc.
b. use dup2
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
                close(fd[0]);
                dup2(fd[1], 1); 
                execlp("ls", "ls", "-l", (char*) NULL);
                // execlp() will write output of "ls -l" to fd with value = 1 (write-end of pipe)
      }
        else {
                close(fd[1]);
                dup2(fd[0], 0); 
                execlp("wc", "wc", (char*) NULL);
                // execlp() will read input from fd with value = 0 (read-end ofpipe) as input to “wc” command and show output to fd with value = 1 =>STDOUT
}
} 
