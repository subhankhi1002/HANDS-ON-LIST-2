/*
============================================================================
Name : 30d.c
Author : Subhankhi Maiti
Description : Write a program to create a shared memory.
d. remove the shared memory
Date: 13th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key;
    int shmid;

    // Generate the same unique key used to create the shared memory segment
    key = ftok(".", 's');

    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Access the existing shared memory segment
    shmid = shmget(key, 0, 0);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory removed.\n");

    return 0;
}

