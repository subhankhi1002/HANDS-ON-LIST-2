/*
============================================================================
Name : 32c.c
Author : Subhankhi Maiti
Description : Write a program to implement semaphore to protect any critical section.
c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 13th Oct, 2023.
============================================================================
*/


#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>

int main(void) 
{
    union semun 
    {
        int val;
    } arg;
    
    key_t key = ftok(".", 1);
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0600);
    if(semid != -1) 
    {
        arg.val = 2;
        semctl(semid, 0, SETVAL, arg);
    } 
    else 
    {
        semid = semget(key, 1, 0600);
    }

    printf("Before critical section\n");
    struct sembuf buff = {0, -1, 0};
    semop(semid, &buff, 1);
    
    printf("Inside critical section\n");

    buff.sem_op = 1;
    printf("Press any key to exit critical section");
    getchar();
    semop(semid, &buff, 1);

    printf("Outside critical section\n");
    return 0;
}

/*OUTPUT
---------
//Terminal 1

Before critical section
Inside critical section
Press any key to exit critical section
Outside critical section

//Terminal 2

Before critical section
Inside critical section
Press any key to exit critical section
Outside critical section
*/
