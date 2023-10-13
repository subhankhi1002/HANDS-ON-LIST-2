/*
============================================================================
Name : 32d.c
Author : Subhankhi Maiti
Description : Write a program to implement semaphore to protect any critical section.
d. remove the created semaphore
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
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    }
    else 
    {
        semid = semget(key, 1, 0600);
    }
    
    semctl(semid, 0, IPC_RMID);

    return 0;
}

/*OUTPUT
---------
$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems
0x010539a0 0          subhankhi     600        1
$ cc 32d.c
./a.out
$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems
*/
