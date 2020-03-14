// Chencheng Xie
// z5237028
// Last Modified: 10/08/2019
// COMP9024 19T2
// Assignment 2: Ordered Word Ladder
// https://wiki.cse.unsw.edu.au/cs9024cgi/19T2/Assignment2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"

#define DICT_LIMIT 1000     //limits of vertices
#define OWLS_LIMIT 99       //limits of path got printed
#define VISITED 1

typedef struct owlRep{
    int numOwls;
    int max_length;
    int **longest_owls;
} *Owl_type;

//Phase 1 functions defined after main()
bool differByOne(char *, char *);
bool changeLetter(char *, char *);
bool addLetter(char *, char *);
bool removeLetter(char *, char *);
//Phase 3 functions defined after main()
Owl_type dfs (Graph, Vertex, int);
void dfsR (Graph, Vertex, int, int [], int *, int, Owl_type, int *);

int main() {
    // Phase 2:
    //read from stdin and store in 'standInput'.
    char * standInput = malloc(sizeof(char));
    if (standInput == NULL) {
        fprintf(stderr, "string intake: out of memory\n");
        return 1;
    }
    //Track the current location of input
    int loc = 0;
    char c;
    while ((c = getchar()) != EOF) {
        *(standInput+loc) = c;
        loc++;
        standInput = realloc(standInput, (loc+1) * sizeof(char));
        if (standInput == NULL) {
            fprintf(stderr, "string intake: out of memory\n");
            return 1;
        }
    }
    //Add the terminater at the end of 'standInput'
    *(standInput+loc) = '\0';

    //array of pointers pointing between 'standInput' where each word starts.
    char * Dictionary[DICT_LIMIT];
    char * cur_word;
    int word_count = 0;
    bool start_word = false;
    for (int i = 0; i <= loc; i++) {
        if (!start_word && standInput[i] >= 'a' &&  standInput[i] <= 'z') {
            //mark the starting of each word and assign its address
            //the new word has started
            cur_word = &standInput[i];
            start_word = true;
        }
        else if (!(standInput[i] >= 'a' &&  standInput[i] <= 'z')) {
            //add '\0' at the end of each word
            standInput[i] = '\0';
            int duplicate = 0;
            //check if this cur_word is duplicated
            //we only check cur_word with last stored word
            //since words are inputted with alphabetical order
            if (word_count >= 1 && !strcmp(Dictionary[word_count - 1], cur_word)) {
                duplicate = 1;
            }
            //We only ddd cur_word to Dictionary if it's not duplicated
            if (!duplicate && start_word) {
                Dictionary[word_count++] = cur_word;
            }
            start_word = false;
        }
    }
    //Print the whole dictionary
    printf("Dictionary\n");
    for (int i = 0; i < word_count; i++) {
        printf("%d: %s\n", i, Dictionary[i]);
    }
    //Insert dictionary into Graph g
    Graph g = newGraph(word_count);
    for (int i = 0; i < word_count-1; i++) {
        for (int j = i+1; j < word_count; j++) {
             //create edge (i,j) if i, j are 'differByOne'
            if (differByOne(Dictionary[i], Dictionary[j])) {
                insertEdge(newEdge(i, j), g);
            }
        }
    }
    //Print the Graph g
    printf("Ordered Word Ladder Graph\n");
    showGraph(g);

    // Phase 3:
    //Use dfs to obtain lists of maximal length OWLS path
    Owl_type owls = dfs(g, 0, word_count);
    // Situation for empty input
    if (owls == NULL) {
        printf("Longest ladder length: 0\nLongest ladders:\n");
        return 0;
    }

    printf("Longest ladder length: %d\nLongest ladders:\n", owls->max_length);
    //for each path in the list
    for (int i = 0; i < owls->numOwls; i++) {
        printf("%2d: ", i+1);
        //for each word in the path
        for (int j = 0; j < owls->max_length - 1; j++) {
            printf("%s -> ", Dictionary[owls->longest_owls[i][j]]);
        }
        //print the last word in the path
        printf("%s\n", Dictionary[owls->longest_owls[i][owls->max_length - 1]]);
    }

    // Finish up:
    for (int i = 0; i < owls->numOwls; i++) {
        //free pointer of each path
        free(owls->longest_owls[i]);
    }
    //free the pointer of list of paths
    free(owls->longest_owls);
    owls->longest_owls = NULL;
    //free OWLS
    free(owls);
    owls =  NULL;
    //free the Graph
    g = freeGraph(g);
    g = NULL;
    //Free the standInput
    free(standInput);
    standInput = NULL;
    return 0;
}
//Phase 1 function to check if two words are differ by one
// takes two string pointers, return true or false
bool differByOne(char * word1, char * word2) {
    if (strlen(word1) == strlen(word2)){
        return changeLetter(word1, word2);
    }
    else if ((strlen(word1) - strlen(word2)) == -1){
        return addLetter(word1, word2);
    }
    else if ((strlen(word1) - strlen(word2)) == 1){
        return removeLetter(word1, word2);
    }
    else {
        return false;
    }
    return false;
}
//Phase 1 function to check if two words with same length are differ by one letter
// takes two string pointers, return true or false
bool changeLetter(char * word1, char * word2) { // ben -> hen
    int diff = 0;
    for (int i = 0; word1[i] != '\0'; i++) {
        if (word1[i] != word2[i]) {
            if (diff == 0 && word2[i] > word1[i]) {
                diff = 1;
            }
            else {
                return false;
            }
        }
    }
    if (!diff) {
        return false;
    }
    return true;
}
//Phase 1 function to check if word_2 is obtain by adding one letter on word_1
// takes two string pointers, return true or false
bool addLetter(char * word1, char * word2) { // band -> brand
    int i;
    for (i = 0; word1[i] != '\0'; i++){
        if (word2[i] > word1[i]) {
            break;
        }
        else if (word2[i] < word1[i]) {
            return false;
        }
    }
    for (int j = i; word1[j] != '\0'; j++){
        if (word1[j] != word2[j+1]) {
            return false;
        }
    }
    return true;
}
//Phase 1 function to check if word_2 is obtain by deleting one letter on word_1
// takes two string pointers, return true or false
bool removeLetter(char * word1, char * word2) { //bran -> ran
    int i;
    for (i = 0; word2[i] != '\0'; i++){
        if (word1[i] < word2[i]) {
            break;
        }
        else if (word1[i] > word2[i]) {
            return false;
        }
    }
    for (int j = i; word2[j] != '\0'; j++){
        if (word1[j+1] != word2[j]) {
            return false;
        }
    }
    return true;
}

//Phase 3 function
// Initialiser for Depth First Search
// returns a pointer to set of pointers
// which each points to one maximal length path vertices list
Owl_type dfs (Graph g, Vertex v, int numV) {
    //numV = 0 when standInput is empty, skip everything
    if (numV == 0) {
        return NULL;
    }
    //allocate memory space for owls
    Owl_type owls = malloc(sizeof(struct owlRep));
    if (owls == NULL) {
        fprintf(stderr, "dfs owls: out of memory\n");
        exit(1);
    }
    //initial values
    owls->numOwls = 0;
    owls->max_length = 0;
    //initialise a list to track if every node is visited or not
    int *visited = malloc(numV*sizeof(int));
    if (visited == NULL) {
        fprintf(stderr, "dfs visited: out of memory\n");
        exit(1);
    }
    //All set to UNVISITED
    for (Vertex i = 0; i < numV; i++) {
        visited[i] = UNVISITED;
    }
    //initialise a list to track the current longest path to each node
    int *nodeCost = malloc(numV*sizeof(int));
    if (nodeCost == NULL) {
        fprintf(stderr, "dfs nodeCost: out of memory\n");
        exit(1);
    }
    ////All set to 0
    for (Vertex i = 0; i < numV; i++) {
        nodeCost[i] = 0;
    }
    //allocate memory space for owl path list
    owls->longest_owls = malloc(OWLS_LIMIT * sizeof(int *));
    if (owls->longest_owls == NULL) {
        fprintf(stderr, "dfs owls->longest_owls: out of memory\n");
        exit(1);
    }
    bool allVisited = false;
    // list to record current path
    int backtrack[DICT_LIMIT];
    // the current path length
    int cur = 0;
    //while some node is not visited, visit it
    while (!allVisited) {
        //call dfsR to recursively search down the graph
        dfsR(g, v, numV, backtrack, visited, cur, owls, nodeCost);
        allVisited = true;
        //if any node is UNVISITED, it not allVisited, visit it next loop
        for (Vertex i = 0; i < numV && allVisited; i++) {
            if (visited[i] == UNVISITED) {
                allVisited = false;
                v = i;
            }
        }
    }
    //free up visited list
    free(visited);
    //free up nodeCost list
    free(nodeCost);
    return owls;
}

// Recursive function to search the graph until no child_node
void dfsR (Graph g, Vertex v, int numV, int backtrack[], int *visited, int cur,
            Owl_type owls, int *nodeCost) {
    //node 'v' is just VISITED
    visited[v] = VISITED;
    //add node 'v' to the current path
    backtrack[cur] = v;
    //if the path to this node is shorter than previous path to this node,
    //no point to keep search
    if (cur < nodeCost[v]) {
        return;
    }
    //if current path to this node is longer than previous path to this node,
    //update the longest path to this node
    else if (cur > nodeCost[v]) {
        nodeCost[v] = cur;
    }
    //variable for whether this node has child_node
    bool child_node = false;
    for (int i = v + 1; i < numV; i++) {
        //find a edge, this node has child_node
        if (isEdge(newEdge(v, i), g)) {
            child_node = true;
            //search down with cur+1
            dfsR(g, i, numV, backtrack, visited, cur+1, owls, nodeCost);
        }
    }
    //if this node has 0 child_node
    //compare current path length with maximal path length we've found
    if (!child_node) {
        //we found longer path
        //reset 'longest_owls' and set it to current path
        if (cur + 1 > owls->max_length) {
            for (int j = 0; j < owls->numOwls; j++) {
                free(owls->longest_owls[j]);
            }
            //update maximal path length
            owls->max_length = cur + 1;
            //reset number of OWLs
            owls->numOwls = 1;
            //record current path as maximal length path
            owls->longest_owls[owls->numOwls - 1] = malloc(owls->max_length * sizeof(int));
            if (owls->longest_owls[owls->numOwls - 1] == NULL) {
                fprintf(stderr, "dfsR owls->longest_owls[owls->numOwls - 1]: out of memory\n");
                exit(1);
            }
            for (int m = 0; m < owls->max_length; m++) {
                owls->longest_owls[owls->numOwls - 1][m] = backtrack[m];
            }
        }
        //we found same length to the maximal length path
        //add current path to the 'longest_owls'
        else if (cur + 1 == owls->max_length) {
            if (owls->numOwls < OWLS_LIMIT) {
                //update number of OWLs, maximal path length is unchanged
                owls->numOwls += 1;
                //add current path to the maximal length path list
                owls->longest_owls[owls->numOwls - 1] = malloc(owls->max_length * sizeof(int));
                if (owls->longest_owls[owls->numOwls - 1] == NULL) {
                    fprintf(stderr, "dfsR owls->longest_owls[owls->numOwls - 1]: out of memory\n");
                    exit(1);
                }
                for (int m = 0; m < owls->max_length; m++) {
                    owls->longest_owls[owls->numOwls - 1][m] = backtrack[m];
                }
            }
        }
    }
    return;
}
