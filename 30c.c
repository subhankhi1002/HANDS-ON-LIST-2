/*
============================================================================
Name : 30c.c
Author : Subhankhi Maiti
Description : Write a program to create a shared memory.
c. detach the shared memory
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
    char *shm_addr;

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

    // Attach the shared memory
    shm_addr = (char *)shmat(shmid, NULL, 0);

    if (shm_addr == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Detach the shared memory using the correct pointer
    if (shmdt(shm_addr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory detached.\n");

    return 0;
}

