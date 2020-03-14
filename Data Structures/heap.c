#include "heap.h"
#define HEAP_LIMIT 1000
#define HEAP_HEAD -9999

struct heaptype{
    int array[HEAP_LIMIT];
    int top;
};

heap createHeap(void) {
    heap hp = malloc(sizeof(struct heaptype));
    if (hp == NULL) {
        fprintf(stderr, "heap.c createHeap: out of memory\n");
        exit(1);
    }
    hp->array[0] = HEAP_HEAD;
    hp->top = 0;
    return hp;
}
void printHeap(heap hp) {
    if (hp == NULL) {
        fprintf(stderr, "heap.c printHeap: heap not initialised\n");
    }
    else if (hp->array[0] != HEAP_HEAD) {
        fprintf(stderr, "heap.c printHeap: heap is corrupted\n");
    }
    else {
        printf("Heap:");
        for (int i = 1; i <= hp->top; i++) {
            printf(" %d", hp->array[i]);
        }
        putchar('\n');
    }
    return;
}
void fixUp(heap hp, int i) {
    if (hp == NULL) {
        fprintf(stderr, "heap.c fixUp: heap not initialised\n");
    }
    else {
        while (hp->array[i] > hp->array[i/2] && i > 1) {
            int temp = hp->array[i/2];
            hp->array[i/2] = hp->array[i];
            hp->array[i] = temp;
            i /= 2;
        }
    }
    return;
}
void fixDown(heap hp, int i) {
    if (hp == NULL) {
        fprintf(stderr, "heap.c fixDown: heap not initialised\n");
    }
    else {
        while (i < hp->top/2 && ( hp->array[i] < hp->array[i*2]|| hp->array[i] < hp->array[i*2+1])) {
            if (hp->array[i*2] > hp->array[i*2+1]) {
                int temp = hp->array[i*2];
                hp->array[i*2] = hp->array[i];
                hp->array[i] = temp;
                i = i*2;
            }
            else {
                int temp = hp->array[i*2+1];
                hp->array[i*2+1] = hp->array[i];
                hp->array[i] = temp;
                i = i*2 + 1;
            }
        }
    }
    return;
}
void insertHeap(heap hp, int data) {
    if (hp == NULL) {
        fprintf(stderr, "heap.c insertHeap: heap not initialised\n");
    }
    else if (hp->top >= HEAP_LIMIT - 1) {
        fprintf(stderr, "heap.c insertHeap: heap overflow\n");
    }
    else {
        hp->top++;
        hp->array[hp->top] = data;
        fixUp(hp, hp->top);
    }
    return;
}
int deleteMax(heap hp) {
    int retval = 0;
    if (hp == NULL) {
        fprintf(stderr, "heap.c deleteMax: heap not initialised\n");
    }
    else if (hp->top < 1) {
        fprintf(stderr, "heap.c deleteMax: heap underflow\n");
    }
    else{
        retval = hp->array[1];
        hp->array[1] = hp->array[hp->top];
        hp->top--;
        fixDown(hp, 1);
    }
    return retval;
}
int isEmpty(heap hp) {
    int empty = 0;
    if (hp == NULL) {
        fprintf(stderr, "heap.c isEmpty: heap not initialised\n");
    }
    else{
        if (hp->top <= 0) {
            empty = 1;
        }
    }
    return empty;
}






//
