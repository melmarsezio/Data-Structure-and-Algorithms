// IOmem.h
// Interface to IOmem ADT that reads input data, builds and print graphs and manages memory.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef GRAPH
#define GRAPH
#include "Graph.h"
#endif

int* mallocArray(int);       // malloc an array of length int * sizeof(int)
void printArray(char *, int *, int); // print an int array of length int
int readNumV(void);
int readBuildGraph(Graph g);
