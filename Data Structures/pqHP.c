#include "pq.h"
#define HEAP_HEAD -9999

struct pqRep{
    int nItems;
    int *items;
    int size;
};

static void fixUp(PQ hp, int i) {
    if (hp == NULL) {
        fprintf(stderr, "pgHP.c fixUp: priority queue not initialised\n");
    }
    else {
        while (hp->items[i] > hp->items[i/2] && i > 1) {
            int temp = hp->items[i/2];
            hp->items[i/2] = hp->items[i];
            hp->items[i] = temp;
            i /= 2;
        }
    }
    return;
}

static void fixDown(PQ hp, int i) {
    if (hp == NULL) {
        fprintf(stderr, "pgHP.c fixDown: priority queue not initialised\n");
    }
    else {
        while (i <= hp->nItems/2 && ( hp->items[i] < hp->items[i*2]|| hp->items[i] < hp->items[i*2+1])) {
            if (hp->items[i*2] > hp->items[i*2+1]) {
                int temp = hp->items[i*2];
                hp->items[i*2] = hp->items[i];
                hp->items[i] = temp;
                i = i*2;
            }
            else {
                int temp = hp->items[i*2+1];
                hp->items[i*2+1] = hp->items[i];
                hp->items[i] = temp;
                i = i*2 + 1;
            }
        }
    }
    return;
}

PQ createPQ(int size) {
    PQ q = malloc(sizeof(struct pqRep));
    if (q == NULL) {
        fprintf(stderr, "pqHP.c createPQ: out of memory\n");
        exit(1);
    }
    q->items = malloc((size+1) * sizeof(int));
    if (q->items == NULL) {
        fprintf(stderr, "pqHP.c createPQ: out of memory\n");
        exit(1);
    }
    q->nItems = 0;
    q->size = size;
    q->items[0] = HEAP_HEAD;
    return q;
}

void insertPQ(PQ q, int it) {
    if (q == NULL) {
        fprintf(stderr, "pqHP.c insertPQ: priority queue not initialised\n");
    }
    else if (q->nItems == q->size) {
        fprintf(stderr, "pqHP.c insertPQ: priority queue overflow\n");
    }
    else {
        q->nItems++;
        q->items[q->nItems] = it;
        fixUp(q, q->nItems);
    }
    return;
}
int delMaxPQ(PQ q) {
    int retval = -1;
    if (q == NULL) {
        fprintf(stderr, "pqHP.c delMaxPQ: priority queue not initialised\n");
    }
    else if (q->nItems == 0) {
        fprintf(stderr, "pqHP.c delMaxPQ: priority queue empty\n");
    }
    else {
        retval = q->items[1];
        q->items[1] = q->items[q->nItems];
        q->nItems--;

        fixDown(q, 1);
    }
    return retval;
}

int isEmptyPQ(PQ q) {
    int empty = 0;
    if (q == NULL) {
        fprintf(stderr, "pqHP.c isEmptyPQ: priority queue not initialised\n");
    }
    else {
        empty = q->nItems == 0;
    }
    return empty;
}

void showPQ(PQ q) {
    if (q == NULL) {
        fprintf(stderr, "pqHP.c showPQ: priority queue not initialised\n");
    }
    else {
        printf("PQ: << ");
        if (isEmptyPQ(q)) {
            printf("");
        }
        else {
            for (int i = 1; i < q->nItems+1; i++) {
                printf("%d ", q->items[i]);
            }
        }
        printf(">>");
    }
    return;
}







//
