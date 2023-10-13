/*
============================================================================
Name : 30b.c
Author : Subhankhi Maiti
Description : Write a program to create a shared memory.
b. attach with O_RDONLY and check whether you are able to overwrite.
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

    // Attach the shared memory for reading (O_RDONLY)
    shm_addr = (char *)shmat(shmid, NULL, SHM_RDONLY);

    if (shm_addr == (char *)(-1)) {
        perror("shmat (read)");
        exit(EXIT_FAILURE);
    }

    // Attempt to overwrite (fails in read-only mode) and give segmentation fault
    //strncpy(shm_addr, "This should not work.", strlen("This should not work."));
    
    // Read and display the data 
    printf("Read from shared memory: %s\n", shm_addr);

    // Detach the shared memory
    if (shmdt(shm_addr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

