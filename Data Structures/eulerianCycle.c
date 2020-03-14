// dfsStack.c: traverse a graph using DFS and stacking (graph may be disconnected)
// Compile using:
//       dcc -o dfsStack dfsStack.c IOmem.c GraphAM.c Quack.c
//
#include <stdio.h>
#include <stdlib.h>

#ifndef GRAPH
#define GRAPH
#include "Graph.h"
#endif

#ifndef QUACK
#define QUACK
#include "Quack.h"
#endif

#ifndef IOMEN
#define IOMEN
#include "IOmem.h"
#endif


#define STARTVERTEX 0   // start the depth-first search at this vertex

int adjacent(Graph g, Vertex v, int numV) {
    int retval = -1;
    for (int w = numV-1; w >= 0 && retval == -1; w--) {
        if (isEdge(newEdge(v, w), g)) {
            retval = w;
            removeEdge(newEdge(v, w), g);
        }
    }
    return retval;
}

void findEulerianCycle(Graph g, Vertex v, int numV) {
    Quack s = createQuack();
    int next;
    printf("Eulerian cycle: ");
    push(v, s);
    while (!isEmptyQuack(s)) {
        v = pop(s);
        push(v, s);
        if ((next = adjacent(g, v, numV)) != -1) {
            push(next, s);
        }
        else {
            printf("%d ", pop(s));
        }
    }
    putchar('\n');
    return;
}

int main(void) {
   int numV;
   if ((numV = readNumV()) > 0) {        // read #vertices
      Graph g = newGraph(numV);
      if (readBuildGraph(g) == 1) {
         showGraph(g);

         findEulerianCycle(g, STARTVERTEX, numV);
      }
      freeGraph(g);
      g= NULL;
   }
   else {
      printf("Error in reading #number\n");
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}
