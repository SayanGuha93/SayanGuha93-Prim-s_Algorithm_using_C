#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define MAX_NODES 50 // Maximum number of nodes
// Node structure for adjacency list
struct node {
    int vertex;
    int weight;
    struct node* next;
};
// Graph structure
struct Graph {
    int numVertices;
    struct node** adjLists;
};
// Create a new node
struct node* createNode(int v, int weight) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
// Create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
    for (int i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;
    return graph;
}
// Add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    // Since it's an undirected graph, add edge in the opposite direction
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
    }
// Priority Queue (Min-Heap) Node
typedef struct {
    int vertex,weight;
} HeapNode;
// Min-Heap Structure
typedef struct {
    HeapNode heap[MAX_NODES];
    int size;
} MinHeap;
// Swap two heap nodes
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}
// Heapify Up
void heapifyUp(MinHeap* h, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (h->heap[parent].weight > h->heap[index].weight) {
            swap(&h->heap[parent], &h->heap[index]);
            index = parent;
        }
        else {
            
        }
    }
}
// Heapify Down
void heapifyDown(MinHeap* h, int index) {
    int left, right, smallest;
    while (1) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;
            if (left < h->size && h->heap[left].weight < h->heap[smallest].weight)
            smallest = left;
            if (right < h->size && h->heap[right].weight < h->heap[smallest].weight)
            smallest = right;
            if (smallest != index) {
            swap(&h->heap[index], &h->heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}
// Push a node into the heap
void push(MinHeap* h, int v, int w) {
    h->heap[h->size].vertex = v;
    h->heap[h->size].weight = w;
    heapifyUp(h, h->size);
    h->size++;
}
// Pop the minimum node from the heap
HeapNode pop(MinHeap* h) {
    HeapNode minNode = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return minNode;
}
// Check if heap is empty
int isEmpty(MinHeap* h) {
    return h->size == 0;
}
// Prim’s Algorithm to find MST
void primMST(struct Graph* graph) {
    int V = graph->numVertices;
    int parent[V]; // Stores constructed MST
    int weight[V]; // Key values to pick minimum weight edge
    int inMST[V]; // Boolean array to track vertices included in MST
    MinHeap pq = {0};
    for (int i = 0; i < V; i++) {
        weight[i] = INT_MAX;
        inMST[i] = 0;
    }
    srand(time(NULL));
    int x = rand()%V;
    printf("%d\n",x);
    weight[x] = 0; // Start from vertex 0
    parent[x] = -1;
    push(&pq, x, weight[x]);
    while (!isEmpty(&pq)) {
        HeapNode minNode = pop(&pq);
        int u = minNode.vertex;
        if (inMST[u]) continue;
        inMST[u] = 1;
        struct node* temp = graph->adjLists[u];
        while (temp) {
            int v = temp->vertex;
            int w = temp->weight;
            if (!inMST[v] && w < weight[v]) {
                weight[v] = w;
                parent[v] = u;
                push(&pq, v, weight[v]);
            }
            temp = temp->next;
        }
    }
    // Print MST
    printf("Edge Weight\n");
    for (int i = 0; i < V; i++)
    if(weight[i]!=INT_MAX && parent[i]!=-1 )
    printf("%d - %d %d\n", parent[i], i, weight[i]);
}
// Main function
int main() {
    int V = 9; // Number of vertices
    struct Graph* graph = createGraph(V);
    // Adding edges
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
    primMST(graph);
    return 0;
}