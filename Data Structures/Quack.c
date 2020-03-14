#include "Quack.h"
#define LIMIT 1000

struct node {
    int array[LIMIT];
    int top;
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
        fprintf(stderr, "Quack.c createQuack: out of memory\n");
        exit(1);
    }
    qs->top = -1;
    return qs;
}

Quack destroyQuack(Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "Quack.c destroyQuack: quack not initialised\n");
    }
    else {
        free(qs);
        qs = NULL;
    }
    return qs;
}

void push(int v, Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "Quack.c push: quack not initialised\n");
    }
    else if (qs->top >= LIMIT - 1) {
        fprintf(stderr, "Quack.c push: quack overflow\n");
    }
    else {
        qs->top++;
        qs->array[qs->top] = v;
    }
    return;
}

void qush(int v, Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "Quack.c qush: quack not initialised\n");
    }
    else if (qs->top >= LIMIT - 1) {
        fprintf(stderr, "Quack.c qush: quack overflow\n");
    }
    else {
        qs->top++;
        for (int i = qs->top; i > 0; i--) {
            qs->array[i] = qs->array[i-1];
        }
        qs->array[0] = v;
    }
    return;
}

int pop(Quack qs) {
    int retval = 0;
    if (qs == NULL) {
        fprintf(stderr, "Quack.c pop: quack not initialised\n");
    }
    else if (qs->top < 0) {
        fprintf(stderr, "Quack.c pop: quack underflow\n");
    }
    else {
        retval = qs->array[qs->top];
        qs->top--;
    }
    return retval;
}

int isEmptyQuack(Quack qs) {
    int retval = 0;
    if (qs == NULL) {
        fprintf(stderr, "Quack.c isEmptyQuack: quack not initialised\n");
    }
    else if (qs->top < 0) {
        retval = 1;
    }
    return retval;
}

void makeEmptyQuack(Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "Quack.c makeEmptyQuack: quack not initialised\n");
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
        fprintf(stderr, "Quack.c showQuack: quack not initialised\n");
    }
    else {
        printf("Quack: <<");
        if (qs->top == -1) {
            printf(" ");
        }
        else {
            for (int i = 0; i < qs->top-1; i++) {
                printf("%d ", qs->array[i]);
            }
            printf("%d", qs->array[qs->top]);
        }
        printf(">>\n");
    }
    return;
}
