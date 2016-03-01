/*************************************
* Lab 3 Exercise 1
* Name:
* Student No:
* Lab Group:
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  // For Predefined constants
#include <sys/ipc.h>    // For POSIX IPC
#include <sys/shm.h>    // For POSIX Shared Memory

int main()
{
    int result;
    int shdMemId;    
    char* shdMemRegion;
    int arraySize;
    int shdMemSize;  //Remember to initialize this before shmget()

    //TODO:Fill In Your Code HERE for reading user input
    printf("Enter Array Size:");
    scanf("%d", &arraySize);
    shdMemSize = 4 * (arraySize + 1);

    //Create a new shared memory region
    shdMemId = shmget( IPC_PRIVATE, shdMemSize, IPC_CREAT | 0666 );
    if (shdMemId < 0){
        printf("Cannot create shared memory region!\n");
        exit(1);
    }
    //printf("Shared Memory Id is %i\n",shdMemId);

    //Attach a new shared memory region
    shdMemRegion = (char*) shmat(shdMemId, NULL, 0);
    if ( shdMemRegion == (char*)-1){
        printf("Cannot attach shared memory region!\n");
        exit(1);
    }
    
    //Shared memory regions remained attached after fork()
    // Parent and child can now communicate with each other!
    result = fork();
    if (result){        //Parent

        //TODO: Fill In Your Code Here
        int v, sumparent, sumchild, sumtotal;
        sumchild = sumparent = sumtotal = 0;
        int* Array = (int*) shdMemRegion;
        printf("EnterStartValue:");
        scanf("%d", &v);
        for(int i = 0; i < arraySize; i++){
            Array[i] = v + i;
        }
        for(int i = arraySize / 2; i < arraySize; i++){
            sumparent += Array[i];
        }
        Array[arraySize] = 9999;
        while(Array[arraySize] != 1111){
            sleep(1);
        }
        sumchild = Array[0];
        sumtotal = sumchild + sumparent;
        printf("Parent Sum = %d\n", sumparent);
        printf("Child Sum = %d\n", sumchild);
        printf("Total = %d\n", sumtotal);
        
        /*Important: Remember to detach the shared memory region*/
        shmdt( shdMemRegion );
    } else {            //Child

        //TODO:Fill in Your Code Here
        int* Array = (int*) shdMemRegion;
        while(Array[arraySize] != 9999){
            sleep(1);
        }
        int sumchild = 0;
        for(int i = 0; i < arraySize / 2; i++){
            sumchild += Array[i];
        }
        Array[0] = sumchild;
        Array[arraySize] = 1111;
        
        /*Important: Remember to detach the shared memory region*/
        shmdt( shdMemRegion );

        return 0;   //Child Ends here

    }

    /*Important: Remember to remove the shared memory region after use!*/
    shmctl(shdMemId, IPC_RMID, NULL); 
    return 0;
}
