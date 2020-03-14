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
#define GOAL 4

void printPath(int * parent, int start, Vertex goal) {
    if (start == goal) {
        printf("%d", start);
    }
    else {
        printPath(parent, start, parent[goal]);
        printf("-->%d", goal);
    }

}

void shortestPath(Graph g, Vertex start, Vertex goal, int numV){
    Quack q =  createQuack();
    int * visited = mallocArray(numV);
    int * parent = mallocArray(numV);
    qush(start, q);
    showQuack(q);
    int order = 0;
    int found = 0;
    visited[start] = order++;
    while (!isEmptyQuack(q) && !found) {
        Vertex cur = pop(q);
        //if (visited[cur] == -1) {
        //visited[cur] = order++;
        printArray("Visited: ", visited, numV);
        for (int i = 0; i < numV; i++) {
            if (visited[i] == -1 && isEdge(newEdge(cur, i), g)) {
                parent[i] = cur;
                visited[i] = order++;
                qush(i, q);
                if (i == goal) {
                    found = 1;
                }
            }
        }
        //}
        showQuack(q);
    }
    if (found) {
        printf("SHORTEST path from %d to %d is ", start, goal);
        printPath(parent, start, goal); // print path from START TO GOAL
        putchar('\n');
    }
    else {
        printf("no path found\n");
    }
    printArray("Visited: ", visited, numV);
    printArray("Parent : ", parent, numV);
    free(visited);
    free(parent);
    makeEmptyQuack(q);
    return;
}

int main (void) {
    int numV;
    if ((numV = readNumV()) > 0) {
        Graph g = newGraph(numV);
        if (readBuildGraph(g)) {
            showGraph(g);
            shortestPath(g, STARTVERTEX, GOAL, numV);
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
