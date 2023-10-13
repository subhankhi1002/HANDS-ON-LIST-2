/*
============================================================================
Name : 31a.c
Author : Subhankhi Maiti
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
Date: 13th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h> // For O_CREAT and O_EXCL
#include <sys/stat.h>

int main() {
    sem_t *sem; // Semaphore pointer
    const char *semaphore_name = "/my_semaphore"; // Unique name for the semaphore

    // Create and initialize the binary semaphore with an initial value of 1
    sem = sem_open(semaphore_name, O_CREAT | O_EXCL, 0644, 1);

    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("Binary semaphore created and initialized.\n");

    // Close and unlink the semaphore (not needed for further use in this program)
    sem_close(sem);
    sem_unlink(semaphore_name);

    return 0;
}

