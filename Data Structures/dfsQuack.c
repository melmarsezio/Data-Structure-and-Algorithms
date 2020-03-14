// dfsStack.c: traverse a graph using DFS and stacking (graph may be disconnected)
// Compile using:
//       dcc -o dfsStack dfsStack.c IOmem.c GraphAM.c Quack.c
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "Quack.h"
#include "IOmem.h"

#define WHITESPACE 100
#define STARTVERTEX 0   // start the depth-first search at this vertex

int readNumV(void) {        // read an int (numV) from stdin
   int numV;
   char w[WHITESPACE];
   scanf("%[ \t\n]s", w);  // skip leading whitespace
   if ((getchar() != '#') ||
       (scanf("%d", &numV) != 1)) {
       fprintf(stderr, "missing number (of vertices)\n");
       return -1;
   }
   return numV;
}

int readBuildGraph(Graph g) {   // read int pairs from stdin
    int success = true;             // returns true if no error
    int v1, v2;
    while (scanf("%d %d", &v1, &v2) != EOF && success) {
        if (!validV(g, v1) || !validV(g, v2)) {
           fprintf(stderr, "unable to read edge\n");
           success = false;
        }
        else {
           insertEdge(newEdge(v1, v2), g);
        }
    }
    return success;
}

void dfsQuack(Graph g, Vertex v, int numV){
    Quack q =  createQuack();
    int * visited = mallocArray(numV);
    push(v, q);
    showQuack(q);
    int allVis = 0;
    int order = 0;
    while (!allVis) {
        while (!isEmptyQuack(q)) {
            Vertex cur = pop(q);
            if (visited[cur] < 0) {
                printArray("Visited: ", visited, numV);
                visited[cur] = order++;
                for (int i = numV - 1; i >= 0; i--) {
                    if (isEdge(newEdge(cur, i), g)) {
                        push(i, q);
                    }
                }
            }
            showQuack(q);
        }
        allVis = 1;
        for (int i = 0; i < numV && allVis; i++) {
            if (visited[i] < 0) {
                printf("Graph is DISCONNECTED\n");
                allVis= 0;
                push(i, q);
                showQuack(q);
            }
        }
    }
    printArray("Visited: ", visited, numV);
    free(visited);
    return;
}

int main (void) {
    int numV;
    if ((numV = readNumV()) > 0) {
        Graph g = newGraph(numV);
        if (readBuildGraph(g)) {
            showGraph(g);
            dfsQuack(g, STARTVERTEX, numV);
        }
        g = freeGraph(g);
        g = NULL;
    }
    else {
        printf("Error in reading #number\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
