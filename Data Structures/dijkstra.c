// Starting code for Dijkstra's algorithm ... COMP9024 19T3

#include <stdio.h>
#include <stdbool.h>
#include "PQueue.h"

#define VERY_HIGH_VALUE 999999

void print_path(Graph g, Vertex source, Vertex dest, int pred[]) {      //添加的代码
    if (source == dest) {
        printf("%d", source);
    }
    else {
        Vertex prev = pred[dest];
        print_path(g, source, prev, pred);
        printf("-%d", dest);
    }
}                                                                   //

void dijkstraSSSP(Graph g, Vertex source) {
   int  dist[MAX_NODES];
   int  pred[MAX_NODES];
   bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
   Vertex s, t;

   PQueueInit();
   int nV = numOfVertices(g);
   for (s = 0; s < nV; s++) {
      joinPQueue(s);
      dist[s] = VERY_HIGH_VALUE;
      pred[s] = -1;
      vSet[s] = true;
   }
   dist[source] = 0;

   /* NEEDS TO BE COMPLETED */                              //添加的代码
   for (int i = 0; i < numOfVertices(g); i++) {
       joinPQueue(i);
   }
   while (!PQueueIsEmpty()) {
       t = leavePQueue(dist);
       for (int i = 0; i < numOfVertices(g); i++){
           int weight = adjacent(g, t, i);
           if (weight && (dist[t] + weight < dist[i])){
               dist[i] = dist[t] + weight;
               pred[i] = t;
           }
       }
       vSet[t] = false;
   }
   for (int i = 0; i < numOfVertices(g); i++) {
       if (pred[i] == -1 && i != source) {
           printf("%d: no path\n", i);
       }
       else {
           printf("%d: distance = %d, shortest path: ", i, dist[i]);
           print_path(g, source, i, pred);
           putchar('\n');
       }
   }
}                                                           //

void reverseEdge(Edge *e) {
   Vertex temp = e->v;
   e->v = e->w;
   e->w = temp;
}

int main(void) {
   Edge e;
   int  n, source;

   printf("Enter the number of vertices: ");
   scanf("%d", &n);
   Graph g = newGraph(n);

   printf("Enter the source node: ");
   scanf("%d", &source);
   printf("Enter an edge (from): ");
   while (scanf("%d", &e.v) == 1) {
      printf("Enter an edge (to): ");
      scanf("%d", &e.w);
      printf("Enter the weight: ");
      scanf("%d", &e.weight);
      insertEdge(g, e);
      reverseEdge(&e);               // ensure to add edge in both directions
      insertEdge(g, e);
      printf("Enter an edge (from): ");
   }
   printf("Done.\n");

   dijkstraSSSP(g, source);
   freeGraph(g);
   return 0;
}
