/*
============================================================================
Name : 30a.c
Author : Subhankhi Maiti
Description : Write a program to create a shared memory.
a. write some data to the shared memory
Date: 13th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key;
    int shmid;
    char *shm_addr;
    const char *data_to_write = "Hello, Shared Memory!";
    int shm_size = 1024; // Size of the shared memory segment

    // Generate a unique key for the shared memory segment
    key = ftok(".", 's');

    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a shared memory segment (or get the existing one)
    shmid = shmget(key, shm_size, IPC_CREAT | IPC_EXCL | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory for writing
    shm_addr = (char *)shmat(shmid, NULL, 0);

    if (shm_addr == (char *)(-1)) {
        perror("shmat (write)");
        exit(EXIT_FAILURE);
    }

    // Write data to the shared memory
    strncpy(shm_addr, data_to_write, strlen(data_to_write));

    printf("Data written to shared memory: %s\n", data_to_write);

    // Detach the shared memory
    if (shmdt(shm_addr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

