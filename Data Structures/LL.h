// LL.h
// ADT interface for a linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct node *List;

List createList(void);    // creates and returns an empty linked list
void putHead(int, List);  // inserts data at the head of the list
void putTail(int, List);  // inserts data at the tail of the list
int getHead(List);        // removes and returns the head of the list
int getTail(List);        // removes and returns the tail of the list
int isEmptyList(List);    // 0/1 if the linked list is empty or not
void showList(List);      // prints the linked list (not the head node)
