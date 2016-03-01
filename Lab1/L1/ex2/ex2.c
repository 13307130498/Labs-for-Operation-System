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

//Function Prototypes
node* insertAt(node*, int, int);
void printList(node*);
void destroyList(node*);



int main()
{
    node* myList = NULL;    //Empty List
    int pos, input;
    
    //Fill in code for input and processing
    while(scanf("%i %i", &pos, &input) == 2){
        myList = insertAt(myList, pos, input);
    }
    
    //Output code coded for you
    printf("My List:\n");
    printList(myList);
    
    destroyList(myList);
    myList = NULL;

    
    printf("My List After Destroy:\n");
    printList(myList);
 
    return 0;
}

//Actual Function Implementations
node* insertAt(node* head, int pos, int newData)
{
    node* p, * q;
    p = (node*) malloc (sizeof(node));
    p -> data = newData;
    if(pos == 0 || head == NULL){
        p -> next = head;
        head = p;
        return head;
    }
    for(q = head; pos > 1 && q -> next != NULL; pos--, q = q -> next);
    p -> next = q -> next;
    q -> next = p;
    return head;    //change this!
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
