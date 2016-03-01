/*************************************
* Lab 4 Exercise 2
* Name: LI HUIYING
* Student No: A0145381H
* Lab Group: 1
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
    
    int initMemSize, requestNumber, arraySize, requestType, requestSize;
    int initAlloMemSizeIndex;
    int totalUsed, totalFree, totalWasted;
    block** Array;
    int* memory;
    scanf("%d", &initMemSize);
    int i, j;
    //Initialize the buddy system
    arraySize = smallestPof2(initMemSize) + 1;
    Array = (block **) malloc(arraySize * sizeof(block*));
    memory = (int *) malloc(initMemSize * sizeof(int));
    block* initBlock = (block *) malloc(sizeof(block));
    totalUsed = totalWasted = 0;
    initBlock -> address = 0;
    initBlock -> next = NULL;
    for(i = 0; i < arraySize; i++){
        Array[i] = NULL;
    }
    Array[arraySize - 1] = initBlock;
    block* tmp1;
    block* tmp2;
    //Print out the arrays
    scanf("%d", &requestNumber);
    for(i = 0; i < requestNumber; i++){
        scanf("%d %d", &requestType, &requestSize);
        if(requestType == 1){
            initAlloMemSizeIndex = smallestPof2(requestSize);
            j = initAlloMemSizeIndex;
            while(j < arraySize && Array[j] == NULL){
                j++;
            }
            if(j >= arraySize){
                printf("-1\n");
            }
            else{
                tmp1 = Array[j];
                Array[j] = Array[j] -> next;
                while(j > initAlloMemSizeIndex){
                    j--;
                    tmp2 = (block *) malloc(sizeof(block));
                    tmp2 -> address = tmp1 -> address + POWEROF2[j];
                    tmp2 -> next = Array[j];
                    Array[j] = tmp2;
                }
                printf("%d\n", tmp1 -> address);
            }
        }
    }
    //Clean up
    for(i = 0; i < arraySize; i++){
       while(Array[i] != NULL){
           tmp1 = Array[i];
           Array[i] = Array[i] -> next;
           free(tmp1);
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
