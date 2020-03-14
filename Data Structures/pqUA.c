#include "pq.h"

struct pqRep{
    int nItems;
    int *items;
    int size;
};

PQ createPQ(int size) {
    PQ q = malloc(sizeof(struct pqRep));
    if (q == NULL) {
        fprintf(stderr, "pqUA.c createPQ: out of memory\n");
        exit(1);
    }
    q->items = malloc(size * sizeof(int));
    if (q->items == NULL) {
        fprintf(stderr, "pqUA.c createPQ: out of memory\n");
        exit(1);
    }
    q->nItems = 0;
    q->size = size;
    return q;
}

void insertPQ(PQ q, int it) {
    if (q == NULL) {
        fprintf(stderr, "pqUA.c insertPQ: priority queue not initialised\n");
    }
    else if (q->nItems == q->size) {
        fprintf(stderr, "pqUA.c insertPQ: priority queue overflow\n");
    }
    else {
        q->items[q->nItems] = it;
        q->nItems++;
    }
    return;
}
int delMaxPQ(PQ q) {
    int retval = -1;
    if (q == NULL) {
        fprintf(stderr, "pqUA.c delMaxPQ: priority queue not initialised\n");
    }
    else if (q->nItems == 0) {
        fprintf(stderr, "pqUA.c delMaxPQ: priority queue empty\n");
    }
    else {
        int max = 0;
        for (int i = 1; i < q->nItems; i++) {
            if (q->items[i] > q->items[max]) {
                max = i;
            }
        }
        retval = q->items[max];
        q->items[max] = q->items[q->nItems-1];
        q->nItems--;
    }
    return retval;
}

int isEmptyPQ(PQ q) {
    int empty = 0;
    if (q == NULL) {
        fprintf(stderr, "pqUA.c isEmptyPQ: priority queue not initialised\n");
    }
    else {
        empty = q->nItems == 0;
    }
    return empty;
}

void showPQ(PQ q) {
    if (q == NULL) {
        fprintf(stderr, "pqUA.c showPQ: priority queue not initialised\n");
    }
    else {
        printf("PQ: << ");
        if (isEmptyPQ(q)) {
            printf("");
        }
        else {
            for (int i = 0; i < q->nItems; i++) {
                printf("%d ", q->items[i]);
            }
        }
        printf(">>");
    }
    return;
}






//
