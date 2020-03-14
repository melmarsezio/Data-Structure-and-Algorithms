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

#ifndef IOMEN
#define IOMEN
#include "IOmem.h"
#endif


#define STARTVERTEX 0   // start the depth-first search at this vertex

int hasCycle(Graph g, Vertex fromV, Vertex v, int numV, int * order, int * visited) {
    int retval = 0;
    visited[v] = *order;
    *order = *order + 1;
    for (int w = 0; w < numV && !retval; w++) {
        if (isEdge(newEdge(w, v), g)) {
            if (visited[w] == -1) {
                printf("traverse edge %d-%d\n", v, w);
                retval = hasCycle(g, v, w, numV, order, visited);
            }
            else {
                if (w != fromV) {
                    printf("traverse edge %d-%d\n", v, w);
                    retval = 1;
                }
            }
        }
    }
    return retval;
}

void searchForCycle(Graph g, Vertex v, int numV) {
    int * visited = mallocArray(numV);
    int order = 0;
    if (hasCycle(g, v, v, numV, &order, visited)) {
        printf("found a cycle\n");
    }
    else {
        printf("no cycle found\n");
    }
    printArray("Visited ", visited, numV);
    free(visited);
    return;
}

int main(void) {
   int numV;
   if ((numV = readNumV()) > 0) {        // read #vertices
      Graph g = newGraph(numV);
      if (readBuildGraph(g) == 1) {
         showGraph(g);

         searchForCycle(g, STARTVERTEX, numV);
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
