/*************************************
* Lab 4 Exercise 1
* Name:
* Student No:
* Lab Group:
*************************************/

#include <stdio.h>
#include <stdlib.h>

#define FREE 0      //To represent a free partition
#define OCCUPIED 1  //To represent an occupied partition

//Declaration of a Linked List Node
//  for handling partition information

//Note: You are free to rewrite / redesign in anyway 

typedef struct BLOCKSTRUCT{
    unsigned int address;       //starting address
    struct BLOCKSTRUCT* next;
} block;

//For easy access 
int POWEROF2[] = {1, 2, 4, 8, 16, 32, 64, 
                    128, 256, 512, 1024, 2048, 4096};

//Helper Functions written for you

unsigned int smallestPof2( unsigned int N );
// Find the smallest S, such that 2^S >= N
//   S is returned

unsigned int buddyOf( unsigned int , unsigned int );
//Return the address of the buddy block, at a particular power of 2


int main(int argc, char** argv)
{
    
    int initMemSize;
    int arraySize;
    block** Array;
    int* memory;
    scanf("%d", &initMemSize);

    //Initialize the buddy system
    arraySize = smallestPof2(initMemSize) + 1;
    Array = (block **) malloc(arraySize * sizeof(block*));
    memory = (int *) malloc(initMemSize * sizeof(int));
    block* initBlock = (block *) malloc(sizeof(block));
    
    initBlock -> address = 0;
    initBlock -> next = NULL;
    Array[arraySize - 1] = initBlock;
    int i;
    //Print out the arrays
    for(i = arraySize - 1; i >= 0; i--){
        if(Array[i] == NULL){
            printf("A[%d]:EMPTY\n", i);
        }
        else{
            printf("A[%d]:[%d]", i, Array[i] -> address);
            for(block* p = Array[i] -> next; p != NULL; p = p -> next){
                printf("-> [%d]", p -> address);
            }
            printf("\n");
        }
    }
    //Clean up
    for(i = 0; i < arraySize; i++){
        if(Array[i] != NULL){
            free(Array[i]);
        }
    }
    free(Array);
    free(memory);
    return 0;
}

unsigned int smallestPof2( unsigned int N )
{
    unsigned int s = 0, pOf2 = 1;

    while( pOf2 < N){
        pOf2 <<= 1;
        s++;
    }

    return s;
}

unsigned int buddyOf( unsigned int addr, unsigned int S )
{
    unsigned int mask = 0xFFFFFFFF << (S-1);
    unsigned int buddyBit = 0x0001 << S;

    return (addr & mask) ^ buddyBit;
}
