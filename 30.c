/*
============================================================================
Name : 30.c
Author : Subhankhi Maiti
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 13th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

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

    // Attach the shared memory for reading (O_RDONLY)
    shm_addr = (char *)shmat(shmid, NULL, SHM_RDONLY);

    if (shm_addr == (char *)(-1)) {
        perror("shmat (read)");
        exit(EXIT_FAILURE);
    }

    // Attempt to overwrite (fails in read-only mode) and gives segmentation fault
    //strncpy(shm_addr, "This should not work.", strlen("This should not work."));
    // Read and display the data (writing is not allowed)
    printf("Read from shared memory: %s\n", shm_addr);

    // Detach the shared memory
    if (shmdt(shm_addr) == -1) {
        perror("shmdt");
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

