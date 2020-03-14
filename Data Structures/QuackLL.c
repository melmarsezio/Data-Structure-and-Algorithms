// QuackLL.c: a linked-list-based implementation of a quack
#include "Quack.h"
#include "limits.h"

#define MARKERDATA INT_MAX // dummy data

struct node {
    int data;
    Quack next;
};

Quack createQuack(void);    // create and return Quack
Quack destroyQuack(Quack);  // remove the Quack
void  push(int, Quack);     // put int on the top of the quack
void  qush(int, Quack);     // put int at the bottom of the quack
int   pop(Quack);           // pop and return the top element on the quack
int   isEmptyQuack(Quack);  // return 1 is Quack is empty, else 0
void  makeEmptyQuack(Quack);// remove all the elements on Quack
void  showQuack(Quack);     // print the contents of Quack, from the top down


Quack createQuack(void) {
    Quack qs = malloc(sizeof(struct node));
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c createQuack: out of memory\n");
        exit(1);
    }
    qs->data = MARKERDATA;
    qs->next = NULL;
    return qs;
}

Quack destroyQuack(Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c destroyQuack: quack not initialised\n");
    }
    else {
        Quack step = qs->next;
        while (step != NULL) {
            free(qs);
            qs = step;
            step = step->next;
        }
        free(qs);
        qs = NULL;
    }
    return qs;
}

void push(int v, Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c push: quack not initialised\n");
    }
    else {
        Quack new = malloc(sizeof(struct node));
        if (new == NULL) {
            fprintf(stderr, "QuackLL.c push: out of memory\n");
        }
        else {
            new->data = v;
            new->next = qs->next;
            qs->next = new;
        }
    }
    return;
}

void qush(int v, Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c qush: quack not initialised\n");
    }
    else {
        Quack step = qs;
        while(qs->next != NULL) {
            qs = qs->next;
        }
        Quack new = malloc(sizeof(struct node));
        if (new == NULL) {
            fprintf(stderr, "QuackLL.c qush: out of memory\n");
        }
        else {
            qs->next = new;
            new->data = v;
            new->next = NULL;
        }
    }
    return;
}

int pop(Quack qs) {
    int retval = 0;
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c pop: quack not initialised\n");
    }
    else if (qs->next == NULL) {
        fprintf(stderr, "QuackLL.c pop: quack underflow\n");
    }
    else {
        Quack top = qs->next;
        retval = top->data;
        qs->next = top->next;
        free(top);
    }
    return retval;
}

int isEmptyQuack(Quack qs) {
    int retval = 0;
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c isEmptyQuack: quack not initialised\n");
    }
    else if (qs->next == NULL) {
        retval = 1;
    }
    return retval;
}

void makeEmptyQuack(Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c makeEmptyQuack: quack not initialised\n");
    }
    else {
        while (!isEmptyQuack(qs)) {
            pop(qs);
        }
    }
    return;
}

void showQuack(Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "QuackLL.c showQuack: quack not initialised\n");
    }
    else {
        printf("Quack: <<");
        if (isEmptyQuack(qs)) {
            printf(" ");
        }
        else {
            printf("%d", qs->next->data);
            for (Quack step = qs->next->next; step != NULL; step = step->next) {
                printf(" %d", step->data);
            }
        }
        printf(">>\n");
    }
    return;
}
