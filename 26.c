/*
============================================================================
Name : 26.c
Author : Subhankhi Maiti
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 6th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>


struct msg {
    long int m_type; // Message type (a numeric identifier for the message)
    char message[80]; // Message data (a character array to store the text)
} myq;

int main() {
    key_t key;
    int msgqid;
    struct msg msg;

    // Generate a unique key
    key = ftok(".", 'a');

    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    msgqid = msgget(key, 0);

    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // User Input
    printf("Enter message type (a positive integer): ");
    scanf("%ld", &msg.m_type);
    printf("Enter message text: ");
    scanf(" %[^\n]", msg.message); // Note the space before %[^\n]

    // Send Message
    if (msgsnd(msgqid, &msg, sizeof(struct msg) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the message queue. Use 'ipcs -q' to check.\n");

    return 0;
}

