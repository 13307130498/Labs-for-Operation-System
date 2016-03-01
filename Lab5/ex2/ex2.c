/*************************************
* Lab 5 Exercise 2
* Name: LI HUIYING
* Matric No: A0145381H
* Lab Group: 1
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LITTLEENDIAN

int convertEndian(int w)
{
#ifdef LITTLEENDIAN
    int result;

    result = (w >> 24) & 0x000000ff;
    result |= (w >> 8) & 0x0000ff00;
    result |= (w << 8) & 0x00ff0000;
    result |= (w << 24) & 0xff000000;
    return result;
#else
    return w;
#endif
}


int main()
{
    int fdIn, option, nItems, nBytes;
    char fileName[40];
    int *ip;
    char buf[1], buffer[4];
    int off;
    int fileSize, i;
    
    //Checking 32-bit vs 64-bit. Do not remove!
    printf("Integer size is %d bytes. Should be 4 bytes (32-bit).\n",
            sizeof(int));
    

    if (sizeof(int) != 4){
        printf("64-bit environment detected!\n");
        printf("Please recompile with \"-m32\" flag\n");
        exit(1);
    }
    
    
    printf("File Name: ");
    scanf("%s", fileName);

    fdIn = open(  fileName, O_RDONLY );

    //TODO: Check for valid file
    if(fdIn == -1){
        printf("Cannot Open\n");
        return 1;
    }
    //TODO: Calculate the file size
    fileSize = lseek(fdIn, 0, SEEK_END);
    printf("Size = %i bytes\n", fileSize);
    lseek(fdIn, 0, SEEK_SET);
    //Read and perform the specified options
    while( scanf("%i %i %i", &option, &nItems, &nBytes) == 3){
        //TODO: Handle the options here
        if(option == 1){
            if(nBytes == 1){
                for(i = 0; i < nItems; i++){
                    if(read( fdIn, buf, 1) == 1){
                        printf("%c ", buf[0]);
                    }
                    else
                        break;
                }
                if(i == 0){
                    printf("failed");
                }
                printf("\n");
            }
            else{
                for(i = 0; i < nItems; i++){
                    if(read( fdIn, buffer, 4) == 4){
                        ip = (int*) &buffer;
                        printf("%d ", convertEndian(*ip)); 
                    }
                    else
                        break;
                }
                if(i == 0){
                    printf("failed");
                }
                printf("\n");
            }
        }
        else if(option == 2){
            off = lseek(fdIn, nItems * nBytes, SEEK_CUR);
            if(off == -1){
                printf("not allowed\n");
            }
            else if(off > fileSize){
                printf("not allowed\n");
                lseek(fdIn, -nItems * nBytes, SEEK_CUR);
            }
            else{
                printf("%d\n", off);
            }
        }
        else if(option == 3){
            off = lseek(fdIn, -nItems * nBytes, SEEK_CUR);
            if(off == -1){
                printf("not allowed\n");
            }
            else{
                printf("%d\n", off);
            }
        }
    }
    
    close( fdIn );  //good practice

    return 0;
}