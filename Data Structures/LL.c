/*
  LL.c
  an ADT for a linked list
 */
 #include "LL.h"
#include "limits.h"

struct node {
    int data;
    List next;
};

List createList(void);    // creates and returns an empty linked list
void putHead(int, List);  // inserts data at the head of the list
void putTail(int, List);  // inserts data at the tail of the list
int getHead(List);        // removes and returns the head of the list
int getTail(List);        // removes and returns the tail of the list
int isEmptyList(List);    // 0/1 if the linked list is empty or not
void showList(List);      // prints the linked list (not the head node)


List createList(void) {
    List marker = malloc(sizeof(struct node));
    if (marker == NULL) {
        fprintf(stderr, "LL.c createList: out of memory\n");
        exit(1);
    }
    marker->data = INT_MAX;
    marker->next = NULL;
    return marker;
}

void putHead(int v, List marker) {
    if (marker == NULL) {
        fprintf(stderr, "LL.c putHead: linked list not initialised\n");
    }
    else {
        List new = malloc(sizeof(struct node));
        if (new == NULL) {
            fprintf(stderr, "LL.c putHead: out of memory\n");
        }
        else {
            new->data = v;
            new->next = marker->next;
            marker->next = new;
        }
    }
    return;
}

void putTail(int v, List marker) {
    if (marker == NULL) {
        fprintf(stderr, "LL.c putTail: linked list not initialised\n");
    }
    else {
        List step = marker;
        while(marker->next != NULL) {
            marker = marker->next;
        }
        List new = createList();
        new->data = v;
        marker->next = new;
    }
    return;
}

int getHead(List marker) {
    int retval = 0;
    if (marker == NULL) {
        fprintf(stderr, "LL.c getHead: linked list not initialised\n");
    }
    else if (marker->next == NULL) {
        fprintf(stderr, "LL.c getHead: linked list underflow\n");
    }
    else {
        List top = marker->next;
        retval = top->data;
        marker->next = top->next;
        free(top);
    }
    return retval;
}

int getTail(List marker) {
    int retval = 0;
    if (marker == NULL) {
        fprintf(stderr, "LL.c getTail: linked list not initialised\n");
    }
    else if (marker->next == NULL) {
        fprintf(stderr, "LL.c getTail: linked list underflow\n");
    }
    else {
        List prev = marker;
        List step = prev->next;
        while (step->next != NULL) {
            prev = step;
            step = step->next;
        }
        prev->next = NULL;
        retval = step->data;
        free(step);
    }
    return retval;
}

int isEmptyList(List marker) {
    int retval = 0;
    if (marker == NULL) {
        fprintf(stderr, "LL.c isEmptyList: linked list not initialised\n");
    }
    else if (marker->next == NULL) {
        retval = 1;
    }
    return retval;
}

void showList(List marker) {
    if (marker == NULL) {
        fprintf(stderr, "LL.c showList: linked list not initialised\n");
    }
    else {
        printf("List: <<");
        if (isEmptyList(marker)) {
            printf(" ");
        }
        else {
            printf("%d", marker->next->data);
            for (List step = marker->next->next; step != NULL; step = step->next) {
                printf(" %d", step->data);
            }
        }
        printf(">>\n");
    }
    return;
}
