#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure for the adjacency list
typedef struct AdjList{
    Node* head;
} AdjList;

// Structure for the graph
typedef struct {
    int numVertices;
    AdjList* array;
} Graph;

// Function to create a new node
Node* newNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));

    for (int i = 0; i < numVertices; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    Node* newNodeSrc = newNode(src);
    newNodeSrc->next = graph->array[dest].head;
    graph->array[dest].head = newNodeSrc;

    // Since the graph is undirected, add an edge from dest to src as well
    Node* newNodeDest = newNode(dest);
    newNodeDest->next = graph->array[src].head;
    graph->array[src].head = newNodeDest;
}

// Function to remove an edge between src and dest
void removeEdge(Graph* graph, int src, int dest) {
    Node* prev = NULL;
    Node* current = graph->array[src].head;
    
    // Find the edge to remove
    while (current != NULL && current->vertex != dest) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL)
            prev->next = current->next;
        else
            graph->array[src].head = current->next;
        free(current);
    }

    // Remove the edge in the opposite direction
    prev = NULL;
    current = graph->array[dest].head;
    while (current != NULL && current->vertex != src) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL)
            prev->next = current->next;
        else
            graph->array[dest].head = current->next;
        free(current);
    }
}


// Function to print the adjacency list representation of the graph
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        Node* temp = graph->array[i].head;
        printf("Adjacency list of vertex %d\n", i);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        Node* current = graph->array[i].head;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
    int numVertices = 5;
    Graph* graph = createGraph(numVertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    printGraph(graph);

    printf("Removing edge between 0 and 1\n");
    removeEdge(graph, 0, 1);
    printGraph(graph);

    freeGraph(graph);


    return 0;
}