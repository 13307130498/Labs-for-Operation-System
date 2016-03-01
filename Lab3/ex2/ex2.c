/*************************************
* Lab 3 Exercise 2
* Name:LI HUIYING
* Student No:A0145381H
* Lab Group:8
*************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>  //For Semaphore. Use "-lrt" to compile

#define N 50000
typedef struct 
{
    sem_t* semPtr;
    int shdMemId;
} semInfoStruct;

void newSemaphore( semInfoStruct* semInfo )
{
    //Create a shared memory region for Semaphore 
    semInfo->shdMemId = shmget( IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0666 );
   
    semInfo->semPtr = (sem_t*) shmat(semInfo->shdMemId, NULL, 0);
}

void destroySempahore( semInfoStruct* semInfo )
{
    shmdt( (char*)semInfo->semPtr );
    shmctl(semInfo->shdMemId, IPC_RMID, NULL); 
}

int main()
{
    int shdMemId, result, i, idx, childStatus;
    int shdMemSize = sizeof(int) * (N+1);  //Size in # of bytes
    int* sharedArray;
    int pCount, cCount, nCount;
    semInfoStruct mutex;

     //Create a new shared memory region
    shdMemId = shmget( IPC_PRIVATE, shdMemSize, IPC_CREAT | 0666 );
    if (shdMemId < 0){
        printf("Cannot create shared memory region!\n");
        exit(1);
    }
    printf("Shared Memory Id is %i\n",shdMemId);

    //Attach a new shared memory region
    sharedArray = (int*) shmat(shdMemId, NULL, 0);
    if ( sharedArray == (int*)-1){
        printf("Cannot attach shared memory region!\n");
        exit(1);
    }

    sharedArray[0] = 1; //index for next item

    //TODO:Fill in Your code here
    //Create and initialize binary sempahore
    newSemaphore(&mutex);
    sem_init(mutex.semPtr, 1, 1);
    result = fork();
    if (result){        //Parent
        int index;
        //TODO:Fill in Your code here
        for(int j = 0; j < 25000; j++){
            sem_wait(mutex.semPtr);
            index = sharedArray[0];
            sharedArray[0]++;
            sem_post(mutex.semPtr);
            sharedArray[index] = 1111;
        }

        //wait for child to finish
        wait(&childStatus);


        //Do NOT change this part
        //Perform Auditing
        printf("Both Parent and Child done producing.\n");
        pCount = cCount = nCount = 0;
        for(i = 1; i < N+1; i++){
            switch(sharedArray[i]){
                case 1111:
                    pCount++;
                    break;
                case 9999:
                    cCount++;
                    break;
                default:
                    nCount++;
            }
        }
        printf("Audit Result: P = %i, C = %i, N = %i\n", 
                pCount, cCount, nCount);
        
        destroySempahore(&mutex);

        /*Important: Remember to detach the shared memory region*/
        shmdt( (char*)sharedArray );
    } else {            //Child

        //TODO:Fill in your code here
	int index;
        for(int j = 0; j < 25000; j++){
            sem_wait(mutex.semPtr);
            index = sharedArray[0];
            sharedArray[0]++;
            sem_post(mutex.semPtr);
            sharedArray[index] = 9999;
        }

        /*Important: Remember to detach the shared memory region*/
        shmdt( (char*)sharedArray );

        return 0;   //Child Ends here

    }

    /*Important: Remember to remove the shared memory region after use!*/
    shmctl(shdMemId, IPC_RMID, NULL); 

    return 0;
}