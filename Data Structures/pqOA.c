#include "pq.h"

struct pqRep{
    int nItems;
    int *items;
    int size;
};

PQ createPQ(int size) {
    PQ q = malloc(sizeof(struct pqRep));
    if (q == NULL) {
        fprintf(stderr, "pqOA.c createPQ: out of memory\n");
        exit(1);
    }
    q->items = malloc(size * sizeof(int));
    if (q->items == NULL) {
        fprintf(stderr, "pqOA.c createPQ: out of memory\n");
        exit(1);
    }
    q->nItems = 0;
    q->size = size;
    return q;
}

void insertPQ(PQ q, int it) {
    if (q == NULL) {
        fprintf(stderr, "pqOA.c insertPQ: priority queue not initialised\n");
    }
    else if (q->nItems == q->size) {
        fprintf(stderr, "pqOA.c insertPQ: priority queue overflow\n");
    }
    else {
        int i = 0;
        while (i < q->nItems && q->items[i] < it) {
            i++;
        }
        int j = q->nItems;
        while (j > i) {
            q->items[j] = q->items[j-1];
            j--;
        }
        q->items[i] = it;
        q->nItems++;
    }
    return;
}
int delMaxPQ(PQ q) {
    int retval = -1;
    if (q == NULL) {
        fprintf(stderr, "pqOA.c delMaxPQ: priority queue not initialised\n");
    }
    else if (q->nItems == 0) {
        fprintf(stderr, "pqOA.c delMaxPQ: priority queue empty\n");
    }
    else {
        q->nItems--;
        retval = q->items[q->nItems];
    }
    return retval;
}

int isEmptyPQ(PQ q) {
    int empty = 0;
    if (q == NULL) {
        fprintf(stderr, "pqOA.c isEmptyPQ: priority queue not initialised\n");
    }
    else {
        empty = q->nItems == 0;
    }
    return empty;
}

void showPQ(PQ q) {
    if (q == NULL) {
        fprintf(stderr, "pqOA.c showPQ: priority queue not initialised\n");
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
