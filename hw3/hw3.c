#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define HEAP_EMPTY(n) (!n)

typedef struct node {
    int vertex;
    int weight;
    struct node *link;
} *nodePointer;

typedef struct {
    int lend;
    int rend;
    int weight;
} edge;

/* number of vertices and edges of input graph */
int numVertices, numEdges;

/* min heap */
edge *heap;

/* min heap operations */
void insert(edge, int *);
edge delete(int *);

/* Prim's algorithm */
void Prim(nodePointer *, int);

/* free grpah */
void freeGraph(nodePointer *);

void main(int argc, char *argv[]) {
    nodePointer *graph;
    int lend, rend, weight;
    FILE *inputFile = fopen(argv[1], "r");

    fscanf(inputFile, "%d", &numVertices);
    fscanf(inputFile, "%d", &numEdges);

    /* allocate and initialize graph G, G={V,empty} */
    graph = malloc(numVertices * sizeof(nodePointer));
    for (int i = 0; i < numVertices; i++)
        graph[i] = NULL;

    /* add edges to graph G */
    for (int i = 0; i < numEdges; i++) {
        // fscanf(inputFile, "%d %d %d", lend, rend, weight);

        // TODO
        fscanf(inputFile, "%d %d %d", &lend, &rend, &weight);

        nodePointer np1 = (nodePointer)malloc(sizeof(struct node));
        np1->vertex = rend;
        np1->weight = weight;
        np1->link = graph[lend];
        graph[lend] = np1;

        nodePointer np2 = (nodePointer)malloc(sizeof(struct node));
        np2->vertex = lend;
        np2->weight = weight;
        np2->link = graph[rend];
        graph[rend] = np2;
    }
    
    fclose(inputFile);

    /* allocate array for min heap: num of elements = 2 * num of edges + 1 */
    heap = malloc((2 * numEdges + 1) * sizeof(edge));

    Prim(graph, 0);

    freeGraph(graph);
    free(heap);
}

void Prim(nodePointer *G, int start) {
    int sum = 0;  /* sum of edge's weight in MST */
    int count = 0;  /* total count of edges in MST */
    int *visited;
    FILE *outputFile = fopen("result.txt", "w"); 
    /* add local varaiable here, if any */ 

    /* alloacate and initialize visited array */
    visited = malloc(numVertices * sizeof(int));
    for(int i = 0; i < numVertices; i++)
        visited[i] = 0;

    /* find and print safe edges */
    
    // TODO
    visited[start] = 1;
    int heapSize = 0;

    for (nodePointer p = G[start]; p != NULL; p = p->link) {
        edge e = {start, p->vertex, p->weight};
        insert(e, &heapSize);
    }

    while (!HEAP_EMPTY(heapSize)) {
        edge e = delete(&heapSize);

        if (!visited[e.rend]) {
            visited[e.rend] = 1;
            fprintf(outputFile, "%d %d %d\n", e.lend, e.rend, e.weight);
            sum += e.weight;
            count++;

            for (nodePointer p = G[e.rend]; p != NULL; p = p->link) {
                edge ne = {e.rend, p->vertex, p->weight};
                insert(ne, &heapSize);
            }
        }
    }

    fprintf(outputFile, "%d\n", sum);  /* sum of weight */
    if (count == numVertices - 1)  /* a minimum spanning tree found */
        fprintf(outputFile, "CONNECTED\n");
    else 
        fprintf(outputFile, "DISCONNECTED\n");
    
    fclose(outputFile);
    free(visited);
}

void insert(edge e, int *n) {
    int i = ++(*n);
    while ((i != 1) && (e.weight < heap[i / 2].weight)) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = e;
}

edge delete(int *n) {
    edge item = heap[1];
    edge last = heap[(*n)--];
    int parent = 1, child = 2;

    while (child <= *n) {
        if ((child < *n) && (heap[child].weight > heap[child + 1].weight))
            child++;
        if (last.weight <= heap[child].weight)
            break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = last;
    return item;
}

void freeGraph(nodePointer *G) {
    for (int i = 0; i < numVertices; i++) {
        nodePointer p = G[i];
        while (p != NULL) {
            nodePointer tmp = p;
            p = p->link;
            free(tmp);
        }
    }
    free(G);
}