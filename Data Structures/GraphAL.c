// GraphAL.c: an adjacency list implementation
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct node *List;
struct node {
  Vertex name;
  List next;
};

struct graphRep {
  int nV;    // #vertices
  int nE;    // #edges
  List *edges; // array of linked lists ... THIS IS THE ADJACENCY LIST
};

Graph newGraph(int numVertices) {
  Graph g = NULL;
  if (numVertices < 0) {
     fprintf(stderr, "newgraph: invalid number of vertices\n");
  }
  else {
     g = malloc(sizeof(struct graphRep));
     if (g == NULL) {
        fprintf(stderr, "newGraph: out of memory\n");
        exit(1);
     }
     g->edges = malloc(numVertices * sizeof(int *));
     if (g->edges == NULL) {
        fprintf(stderr, "newGraph: out of memory\n");
        exit(1);
     }
     int v;
     for (v = 0; v < numVertices; v++) {
       g->edges[v] = NULL;
     }
     g->nV = numVertices;
     g->nE = 0;
  }
  return g;
}

Graph freeGraph(Graph g) {

   for (int i = 0; i < g->nV; i++) {
       List p = g->edges[i];
       if (p == NULL) {
           continue;
       }
       while (p->next != NULL) {
           List temp = p->next;
           free(p);
           p = temp;
       }
   }
   free(g->edges);
   free(g);
   g = NULL;
   return g;
}

void showGraph(Graph g) { // print a graph
    if (g == NULL) {
        printf("NULL graph\n");
    }
    else {
        printf("V=%d, E=%d\n", g->nV, g->nE);
        int i;
        for (i = 0; i < g->nV; i++) {
            int nshown = 0;
            List vx = g->edges[i];
            while (vx != NULL) {
               printf("<%d %d> ", i, vx->name);
               nshown++;
               vx = vx->next;
            }
            if (nshown > 0) {
                printf("\n");
            }
        }
    }
    return;
}

static int validV(Graph g, Vertex v) { // checks if v is in graph
    return (v >= 0 && v < g->nV);
}

Edge newE(Vertex v, Vertex w) {
  Edge e = {v, w};
  return e;
}

void showE(Edge e) { // print an edge
    printf("<%d %d>", e.v, e.w);
    return;
}

int isEdge(Graph g, Edge e) {
// a linear search for edge 'e': return 1 if edge found, 0 otherwise
   int found = 0;
   List p = g->edges[e.v];
   if (p == NULL) {
       return found;
   }
   while (p->next != NULL) {
       if (p->name == e.w) {
           found = 1;
           break;
       }
       p = p->next;
   }
   return found;
}

void insertE(Graph g, Edge e){ // edge is e.v---e.w
  if (g == NULL) {
     fprintf(stderr, "insertE: graph not initialised\n");
  }
  else {
     if (!validV(g, e.v) || !validV(g, e.w)) {
        fprintf(stderr, "insertE: invalid vertices <%d %d>\n", e.v, e.w);
     }
     else {
        if (isEdge(g, e) == 0) {
           List n1 = malloc(sizeof(struct node));
           List n2 = malloc(sizeof(struct node));
           if (n1 == NULL || n2 == NULL) {
              fprintf(stderr, "Out of memory\n");
              exit(1);
           }
           n1->name = e.w;           // node contains w
           n1->next = g->edges[e.v]; // node's next is v's linked list
           g->edges[e.v] = n1;       // node is new head for v

           n2->name = e.v;
           n2->next = g->edges[e.w];
           g->edges[e.w] = n2;

           g->nE++;
       }
    }
  }
  return;
}

static int removeV(Graph g, Vertex v, Vertex w) { // return 1 if found&removed
   int success = 0;
   List p = g->edges[v];
   if (p == NULL) {
       return success;
   }
   else if (p->name == w) {
       g->edges[v] = p->next;
       free(p);
       success = 1;
       return success;
   }
   while (p->next != NULL) {
       if (p->next->name == w) {
           List temp = p->next;
           p->next = temp->next;
           free(temp);
           success = 1;
           break;
       }
       p = p->next;
   }
   return success;
}

void removeE(Graph g, Edge e) {
  if (g == NULL) {
     fprintf(stderr, "removeE: graph not initialised\n");
  }
  else {
     if (!validV(g, e.v) || !validV(g, e.w)) {
        fprintf(stderr, "removeE: invalid vertices %d-%d\n", e.v, e.w);
     }
     else {
        if (removeV(g, e.w, e.v) == 1) { // remove v from w's list
           g->nE--;                      // decrement nE if an edge is removed
        }
        removeV(g, e.v, e.w);            // remove w from v's list
     }
  }
  return;
}
