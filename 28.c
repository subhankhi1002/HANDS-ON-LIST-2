/*
============================================================================
Name : 28.c
Author : Subhankhi Maiti
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 13th Oct, 2023.
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

    // Get the current information about the message queue
    struct msqid_ds queue_info;

    if (msgctl(msgqid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl (IPC_STAT)");
        exit(EXIT_FAILURE);
    }

    // Modify the permission bits in the message queue information
    queue_info.msg_perm.mode = 0644; // Change to the desired permissions

    // Set the modified information back to the message queue
    if (msgctl(msgqid, IPC_SET, &queue_info) == -1) {
        perror("msgctl (IPC_SET)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue permissions changed.\n");

    return 0;
}

