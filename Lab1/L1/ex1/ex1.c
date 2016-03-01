/*************************************
* Lab 1 Exercise 1
* Name:Li Huiying
* Matric No:A0145381H
* Lab Group:
*************************************/

#include <stdio.h>
#include <stdlib.h> //for malloc() and free()

//Declaration of a Linked List Node
typedef struct NODE{
    int data;
    struct NODE* next;
} node;
    
//Function prototypes
node* addToHead(node*, int);
void printList(node* );
void destroyList(node* );

int main()
{
    //The skeleton of the input/output is coded for you
    //You are free to add code for debug purpose etc
    //Make sure the ouput matches with the sample given
    node* myList = NULL;    //Empty List
    int input;

    
    while (scanf("%i",&input) == 1){
        myList = addToHead(myList, input);
    } 

    //Print out the linked list
    printf("My List:\n");
    printList(myList);
    
    destroyList(myList);
    myList = NULL;

    //Print out the linked list after destruction
    printf("My List After Destroy:\n");
    printList(myList);
    

    return 0;
}

//Function Implementations
node* addToHead(node* head, int newData)
{
    node *p;
    p = (node*) malloc (sizeof(node));
    p->data = newData;
    p->next = head;
    head = p;


    return head;    //change this
}

void printList(node* head)
//Purpose: Print out the linked list content
//Assumption: the list is properly null terminated
{

    //This function has been implemented for you
    node* ptr = head;

    while (ptr != NULL)  {    //or you can write while(ptr)
        printf("%i ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void destroyList(node* head)
{
    node* p;
    while(head != NULL){
        p = head;
        head = head -> next;
        free(p);
    }
}