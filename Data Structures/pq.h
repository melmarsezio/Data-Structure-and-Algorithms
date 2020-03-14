// pq.h: ADT interface for a priority queue
#include <stdio.h>
#include <stdlib.h>

typedef struct pqRep *PQ;

PQ   createPQ(int size);
void insertPQ(PQ q, int it);
int  delMaxPQ(PQ q);
int  isEmptyPQ(PQ q);
void showPQ(PQ q);
