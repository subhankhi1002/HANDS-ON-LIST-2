/*
============================================================================
Name : 25.c
Author : Subhankhi Maiti
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 6th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int main() {
    key_t key;
    int msgqid;
    struct msqid_ds queue_info;

    // Generate a unique key
    key = ftok(".", 'M');

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

    // Get the message queue information
    if (msgctl(msgqid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    // Access permissions
    printf("Access Permissions: %o\n", queue_info.msg_perm.mode);

    // UID and GID
    printf("UID: %d\n", queue_info.msg_perm.uid);
    printf("GID: %d\n", queue_info.msg_perm.gid);

    // Time of last message sent and received
    printf("Time of Last Message Sent: %s", ctime(&queue_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&queue_info.msg_rtime));

    // Time of last change in the message queue
    printf("Time of Last Change: %s", ctime(&queue_info.msg_ctime));

    // Size of the queue (in bytes)
    printf("Size of the Queue: %lu bytes\n", (unsigned long)queue_info.msg_cbytes);

    // Number of messages in the queue
    printf("Number of Messages in the Queue: %lu\n", (unsigned long)queue_info.msg_qnum);

    // Maximum number of bytes allowed in the queue
    printf("Maximum Number of Bytes Allowed: %lu bytes\n", (unsigned long)queue_info.msg_qbytes);

    // PID of the msgsnd and msgrcv processes
    printf("PID of msgsnd: %d\n", queue_info.msg_lspid);
    printf("PID of msgrcv: %d\n", queue_info.msg_lrpid);

    return 0;
}

