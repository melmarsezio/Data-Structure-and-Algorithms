#include "IOmem.h"

#define WHITESPACE 100

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

int* mallocArray(int num){      // malloc an array of length int * sizeof(int)
    int * array = malloc(num * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "IOmem.c mallocArray: out of memory\n");
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        array[i] = -1;
    }
    return array;
}
void printArray(char * string, int * array, int len){   // print an int array of length int
    printf("%s{", string);
    if (len != 0) {
        for (int i = 0; i < len-1; i++) {
            printf("%d, ", array[i]);
        }
        printf("%d", array[len-1]);
    }
    else {
        printf(" ");
    }
    printf("}\n");
}



//
