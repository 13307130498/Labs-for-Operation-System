/*************************************
* Lab 5 Exercise 1
* Name:
* Matric No:
* Lab Group:
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
    int fdIn,  fileSize;
    int *ip;
    char fileName[40], buffer[4];

    //Checking 32-bit vs 64-bit. Do not remove!
    printf("Integer size is %d bytes. Should be 4 bytes (32-bit).\n",
            sizeof(int));
    

    if (sizeof(int) != 4){
        printf("64-bit environment detected!\n");
        printf("Please recompile with \"-m32\" flag\n");
        exit(1);
    }

    //Program proper
    printf("File Name: ");
    scanf("%s", fileName);

    //Open file for read only
    fdIn = open(  fileName, O_RDONLY );

    //TODO:Check for valid file
    if(fdIn == -1){
        printf("Cannot Open\n");
        return 1;
    }
    //TODO:Calculate the file size
    
    fileSize = lseek(fdIn, 0, SEEK_END);   //change this line
    printf("Size = %i bytes\n", fileSize);
    lseek(fdIn, 0, SEEK_SET);
    //TODO: Change the code below so that it reads until the end of file
    // Right now, this only read the first item.
    while(read( fdIn, buffer, 4) > 0){
        ip = (int*) &buffer;
        printf("%d\n", convertEndian(*ip)); 
    }
    

    //This is how you can "convert" bytes into a single integer
    
    close( fdIn );  //good practice

    return 0;
}
