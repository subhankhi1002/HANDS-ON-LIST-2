/*
============================================================================
Name : 24.c
Author : Subhankhi Maiti
Description : Write a program to create a message queue and print the key and message queue id.
Date: 6th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    key_t key;
    int msgqid;

    // Generate a unique key
    key = ftok(".", 'a');

    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msgqid = msgget(key, IPC_CREAT | 0666);

    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue Key: %x\n", (unsigned int)key);
    printf("Message Queue ID: %d\n", msgqid);

    return 0;
}

