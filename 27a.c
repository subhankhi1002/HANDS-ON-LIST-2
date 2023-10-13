/*
============================================================================
Name : 27a.c
Author : Subhankhi Maiti
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
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

    // Receive a message with 0 as a flag (blocking)
    if (msgrcv(msgqid, &msg, sizeof(struct message) - sizeof(long), 0, 0) == -1) {
        perror("msgrcv (blocking)");
        exit(EXIT_FAILURE);
    }

    printf("Received (blocking) - Type: %ld, Message: %s\n", msg.m_type, msg.m_text);

    return 0;
}

