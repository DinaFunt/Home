#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


typedef struct Node {

    int value;
    struct Node *next;

} Node;

typedef struct linkedList {

    Node *head;
    int length;

} LinkedList;

Node *CreateNode(int val);
void push(LinkedList *list);
LinkedList *CreateList(int n);
Node *getLast(LinkedList *list);
void pushBack(LinkedList *list);
void pushAfter(LinkedList *list);
void printLinkedList(LinkedList *list);
void CleanList(LinkedList *list);
void deleteNode(LinkedList *list);
void orderChange(LinkedList *list);
void makeRound(LinkedList *list);
void circleCheck(LinkedList *list);
void ExitDelete(LinkedList *list);


#endif // LIST_H_INCLUDED
