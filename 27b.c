/*
============================================================================
Name : 27b.c
Author : Subhankhi Maiti
Description : Write a program to receive messages from the message queue.
b. with IPC_NOWAIT as a flag
Date: 6th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_MESSAGE_SIZE 256

struct message {
    long int m_type;
    char m_text[MAX_MESSAGE_SIZE];
} myq;

int main() {
    key_t key;
    int msgqid;
    struct message msg;

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

    // Try to receive a message with IPC_NOWAIT as a flag (non-blocking)
    if (msgrcv(msgqid, &msg, sizeof(struct message) - sizeof(long), 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message available (non-blocking)\n");
        } else {
            perror("msgrcv (non-blocking)");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received (non-blocking) - Type: %ld, Message: %s\n", msg.m_type, msg.m_text);
    }

    return 0;
}

