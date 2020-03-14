#include <stdio.h>
#include <stdlib.h>

typedef struct heaptype *heap;

heap createHeap(void);
void printHeap(heap hp);
//void fixUp(heap hp, int i);
//void fixDown(heap hp, int i);
void insertHeap(heap hp, int data);
int deleteMax(heap hp);
int isEmpty(heap hp);
