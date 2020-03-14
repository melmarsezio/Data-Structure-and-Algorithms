#include "Graph.h"

struct graphRep {
    int numV;
    int numE;
    int **edges;
};

// struct edgeRep{                  // define an EDGE
//   Vertex v;
//   Vertex w;
// };


Graph newGraph(int numV) {
    Graph g = NULL;
    if (numV < 0) {
        fprintf(stderr, "GraphAM.C newGraph: invalid number of vertices\n");
    }
    else {
        g = malloc(sizeof(struct graphRep));
        if (g == NULL) {
            fprintf(stderr, "GraphAM.C newGraph: out of memroy\n");
            exit(1);
        }
        g->edges = malloc(numV * sizeof(int *));
        if (g->edges == NULL) {
            fprintf(stderr, "GraphAM.C newGraph: out of memroy\n");
            exit(1);
        }
        for (int v = 0; v < numV; v++) {
            g->edges[v] = malloc(numV * sizeof(int));
            if (g->edges[v] == NULL) {
                fprintf(stderr, "GraphAM.C newGraph: out of memroy\n");
                exit(1);
            }
            for (int w = 0; w < numV; w++) {
                g->edges[v][w] = 0;
            }
        }
        g->numV = numV;
        g->numE = 0;
    }
    return g;
}

Graph freeGraph(Graph g) {
    if (g == NULL) {
        fprintf(stderr, "GraphAM.C freeGraph: graph not initialised\n");
    }
    else {
        for (int v = 0; v < g->numV; v++) {
            free(g->edges[v]);
        }
        free(g->edges);
        free(g);
        g = NULL;
    }
    return g;
}

void showGraph(Graph g) {
    if (g == NULL) {
        printf("GraphAM.c showGraph: NULL graph\n");
    }
    else {
        printf("V=%d, E=%d\n", g->numV, g->numE);
        for (int v = 0; v < g->numV; v++) {
            int shown = 0;
            for (int w = 0; w < g->numV; w++) {
                if (isEdge(newEdge(v,w), g)) {
                    printf("<%d %d>", v, w);
                    shown++;
                }
                // else {
                //     printf("     ");
                // }
            }
            if (shown) {
                putchar('\n');
            }
        }
    }
    return;
}

Edge newEdge(Vertex v, Vertex w) {
    Edge e;
    e.v = v;
    e.w = w;
    //Edge e = {v, w};
    return e;
}

void insertEdge(Edge e, Graph g) {
    if (g == NULL) {
        fprintf(stderr, "GraphAM.C insertEdge: graph not initialised\n");
    }
    else if (e.v >= g->numV ||  e.w >= g->numV) {
        fprintf(stderr, "GraphAM.C insertEdge: invalid vertices\n");
    }
    else {
        if (!isEdge(e, g)) {
            g->numE++;
        }
        g->edges[e.v][e.w] = 1;
        g->edges[e.w][e.v] = 1;
    }
    return;
}

void removeEdge(Edge e, Graph g) {
    if (g == NULL) {
        fprintf(stderr, "GraphAM.C removeEdge: graph not initialised\n");
    }
    else if (e.v >= g->numV ||  e.w >= g->numV) {
        fprintf(stderr, "GraphAM.C removeEdge: invalid vertices\n");
    }
    else {
        if (g->edges[e.v][e.w]) {
            g->edges[e.v][e.w] = 0;
            g->edges[e.w][e.v] = 0;
            g->numE--;
        }
    }
    return;
}

void showEdge(Edge e) {
     printf("<%d %d>", e.v, e.w);
     return;
}

int isEdge(Edge e, Graph g) {
    int retval = 0;
    if (g == NULL) {
        fprintf(stderr, "GraphAM.C isEdge: graph not initialised\n");
    }
    else if (e.v >= g->numV ||  e.w >= g->numV) {
        fprintf(stderr, "GraphAM.C isEdge: invalid vertices\n");
    }
    else {
        if (g->edges[e.v][e.w]) {
            retval = 1;
        }
    }
    return retval;
}

int validV(Graph g, Vertex v) {
    return (v >= 0 && v < g->numV);
}
