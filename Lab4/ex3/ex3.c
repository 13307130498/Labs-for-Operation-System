/*************************************
* Lab 4 Exercise 3
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


typedef struct OCCUPIEDBLOCKSTRUCT{
    unsigned int address;       //starting address
    unsigned int size;
    unsigned int wasted;
    struct OCCUPIEDBLOCKSTRUCT* next;
} occupiedBlock;

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
    occupiedBlock* occupiedList;
    totalUsed = totalWasted = 0;
    initBlock -> address = 0;
    initBlock -> next = NULL;
    occupiedList = NULL;
    for(i = 0; i < arraySize; i++){
        Array[i] = NULL;
    }
    Array[arraySize - 1] = initBlock;
    block* tmp1;
    block* tmp2;
    block* tmp5;
    occupiedBlock* tmp3;
    occupiedBlock* tmp4;
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
                tmp3 = (occupiedBlock*) malloc(sizeof(occupiedBlock));
                tmp3 -> address = tmp1 -> address;
                tmp3 -> size = POWEROF2[j];
                tmp3 -> wasted = tmp3 -> size - requestSize;
                tmp3 -> next = occupiedList;
                occupiedList = tmp3;
                printf("%d\n", tmp1 -> address);
                free(tmp1);
            }
        }
        else if(requestType == 2){
            tmp3 = occupiedList;
            while(tmp3 != NULL){
                if(tmp3 -> address == requestSize){
                    break;
                }
                tmp3 = tmp3 -> next;
            }
            if(tmp3 == NULL){
                printf("failed\n");
            }
            else{
                printf("ok\n");
                if(occupiedList == tmp3){
                    occupiedList = occupiedList -> next;
                }
                else{
                    for(tmp4 = occupiedList; tmp4 -> next != tmp3; tmp4 = tmp4 -> next);
                    tmp4 -> next = tmp3 -> next;
                }
                tmp1 = (block *) malloc(sizeof(block));
                tmp1 -> address = tmp3 -> address;
                initAlloMemSizeIndex = smallestPof2(tmp3 -> size);
                free(tmp3);
                for(j = initAlloMemSizeIndex; j < arraySize; j++){
                    int buddyAddr = buddyOf(requestSize, j);
                    tmp2 = Array[j];
                    while(tmp2 != NULL){
                        if(tmp2 -> address == buddyAddr){
                            break;
                        }
                        tmp2 = tmp2 -> next;
                    }
                    if(tmp2 == NULL){
                        tmp1 -> next = Array[j];
                        Array[j] = tmp1;
                        break;
                    }
                    else{
                        if(Array[j] -> address == buddyAddr){
                            tmp2 = Array[j];
                            Array[j] = Array[j] -> next;
                        }
                        else{
                            for(tmp5 = Array[j]; tmp5 -> next != tmp2; tmp5 = tmp5 -> next);
                            tmp5 -> next = tmp5 -> next -> next;
                        }
                        if(tmp1 -> address > tmp2 -> address){
                            tmp1 -> address = tmp2 ->address;
                        }
                        free(tmp2);
                    }
                }
            }
        }
    }
    tmp3 = occupiedList;
    while(tmp3 != NULL){
        totalUsed += tmp3 -> size;
        totalWasted += tmp3 ->wasted;
        tmp3 = tmp3 -> next;
    }
    totalFree = initMemSize - totalUsed;
    printf("%d\n%d\n%d\n", totalUsed, totalFree, totalWasted);
    //Clean up
    for(i = 0; i < arraySize; i++){
       while(Array[i] != NULL){
           tmp1 = Array[i];
           Array[i] = Array[i] -> next;
           free(tmp1);
        }
    }
    while(occupiedList != NULL){
        tmp3 = occupiedList;
        occupiedList = occupiedList -> next;
        free(tmp3);
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
