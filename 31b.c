/*
============================================================================
Name : 31b.c
Author : Subhankhi Maiti
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a counting semaphore
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
    unsigned int initial_value = 3; // Initial value for the counting semaphore

    // Create and initialize the counting semaphore
    sem = sem_open(semaphore_name, O_CREAT | O_EXCL, 0644, initial_value);

    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("Counting semaphore created and initialized with value %u.\n", initial_value);

    // Close and unlink the semaphore (not needed for further use in this program)
    sem_close(sem);
    sem_unlink(semaphore_name);

    return 0;
}

