/*************************************
* Lab 1 Exercise 3
* Name     :Li Huiying
* Matric No:A0145381H
* Lab Group:
*************************************/

#include <stdio.h>

//Datatype Declarations
typedef int (*arithFuncPtr)(int, int);


//Function Prototypes
int add(int x, int y);
int subtract(int x, int y);
int multiply(int x, int y);
int divide(int x, int y);


int main()
{
    int a, b, optype, res;

    //The code below is to show the usage of a function pointer only
    //You can remove/comment them off 

    //arithFuncPtr is a function pointer datatype
    // it points to afunction that takes (int, int) as parameter
    //  and returns int as return result
    arithFuncPtr ptr[4];
    ptr[0] = add;
    ptr[1] = subtract;
    ptr[2] = multiply;
    ptr[3] = divide;
    while(scanf("%d %d %d", &a, &b, &optype) == 3){
        printf("%d\n", (* ptr[optype - 1]) (a, b));  
    }


    //Defereference a function pointer === call the function
    //if you take (*ptr) as some function f
    // then below is the same as
    //   res = f(a, b);

   
    return 0;
}

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int divide(int x, int y)
{
    if(y == 0){
        printf("Division by zero!\n");
        return 0;
    }
    return x / y;
}



