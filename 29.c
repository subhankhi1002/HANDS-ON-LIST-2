/*
============================================================================
Name : 29.c
Author : Subhankhi Maiti
Description : Write a program to remove the message queue.
Date: 13th Oct, 2023.
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

    // Generate the same unique key used to create the message queue
    key = ftok(".", 'a');

    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Access the existing message queue
    msgqid = msgget(key, 0);

    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Remove the message queue with IPC_RMID command
    if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
        perror("msgctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed.\n");

    return 0;
}

