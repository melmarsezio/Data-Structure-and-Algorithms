# Ordered Word Ladders
## Coursework assignment for Data Structure and Algorithms
![](https://github.com/melmarsezio/Data-Structure-and-Algorithms/blob/master/Ordered%20Word%20Ladders/owls.jpg)
### Specification
In regards to problem description, input format, output messages, details are explained in *`Assignment2.pdf`*
### Instruction
> cmd run `make` to compile `owl.c`, `GraphAM.c` and `Quack.c` into `owl`
>>  `./owl` to execute it or `./owl < tests/case-[#test].in` to test the file with predefined testcases
>
> or
>> cmd run `chmod +x ./autotest.sh` to give permission to the shellscript, and
>>
>> cmd run `./autotest.sh` to automatically run all testfiles
>
> Sample input:  
> &emsp;&emsp;an at in it on  
> Expected ouput:  
> &emsp;&emsp;Dictionary  
> &emsp;&emsp;0: an  
> &emsp;&emsp;1: at  
> &emsp;&emsp;2: in  
> &emsp;&emsp;3: it  
> &emsp;&emsp;4: on  
> &emsp;&emsp;Ordered Word Ladder Graph  
> &emsp;&emsp;V=5, E=6  
> &emsp;&emsp;<0 1> <0 2> <0 4>  
> &emsp;&emsp;<1 0> <1 3>  
> &emsp;&emsp;<2 0> <2 3> <2 4>  
> &emsp;&emsp;<3 1> <3 2>  
> &emsp;&emsp;<4 0> <4 2>  
> &emsp;&emsp;Longest ladder length: 3  
> &emsp;&emsp;Longest ladders:  
> &emsp;&emsp; 1: an -> at -> it  
> &emsp;&emsp; 2: an -> in -> it  
> &emsp;&emsp; 3: an -> in -> on  

### `Quack.c` description
>#### Data Structure:
>+ `struct node`: a Quack data type (combination of stack and queue), it includes:  
&emsp;&emsp;`array` contains all numbers in the `Quack` (combination of `queue` and `stack`)  
&emsp;&emsp;`top` records the top index of the array
>+ `Quack`: pointer to the `node` type
>#### Functions:
>+ `Quack createQuack(void)`: request memory space for creating `Quack`
>+ `void push(int data, Quack qs)`: push `data` into `qs`, here `qs` acts more like `stack`
>+ `void qush(int data, Quack que)`: qush (queue-push, same as enqueue) `data` into `que`, `que` acts like `queue`
>+ `int pop(Quack qs)`: pop `top` of the `Quack`
>+ `void makeEmptyQuack(Quack qs)`: empty the entire `Quack`
>+ `Quack destroyQuack(Quack qs)`: clean up memory space used by `Quack`
>+ `int isEmptyQuack(Quack qs)`: tell if `qs` is empty or not
>+ `void showQuack(Quack qs)`: print out all elements in the `Quack`
### `GraphAM.c` description
>#### Data Structure:
>+ `struct graphRep`: a graph data type represented by Adjacency Matrix, it includes:  
&emsp;&emsp;`nV`: records number of vertexes in `graphRep`  
&emsp;&emsp;`nE`: records number of edges in `graphRep`  
&emsp;&emsp;`**edges`: 2D matrix of Booleans (`edges[x][y] == 1` means edge `x-y`)
>+ `Graph`: pointer to the `graphRep` type
>+ `Edge`: data type represents an edge between `Edge.v` and `Edge.w`
>#### Functions:
>+ `Graph newGraph(int numVertices)`
>+ `Graph freeGraph(Graph g)`
>+ `void showGraph(Graph g)`
>+ `Edge newEdge(Vertex v, Vertex w)`
>+ `void showEdge(Edge e)`
>+ `int isEdge(Edge e, Graph g)`
>+ `void insertEdge(Edge e, Graph g)`
>+ `void removeEdge(Edge e, Graph g)`

### `owl.c` description
>#### Data Structure:
>+ `struct owlRep`:
>+ `Owl_type`: pointer to the `owlRep` type
>#### Functions:
>+ `bool differByOne(char * word1, char * word2)`
>+ `bool changeLetter(char * word1, char * word2)`
>+ `bool addLetter(char * word1, char * word2)`
>+ `bool removeLetter(char * word1, char * word2)`
>+ `Owl_type dfs (Graph g, Vertex v, int numV)`
>+ `void dfsR (Graph g, Vertex v, int numV, int backtrack[], int *visited, int cur,
            Owl_type owls, int *nodeCost)`

### Testfiles
> all testcases are stored under `tests`, `case-[*].in` represent inputs and `case-[*].exp` represent corresponding expected outputs.

