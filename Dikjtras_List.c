// using list

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Structure to represent a node in adjacency list
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent a graph
struct Graph {
    int V;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest.  A new node is added to the adjacency list of src.
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the distance of each node from the source
void printSolution(int dist[], int n, int src) {
    printf("Distance of each node from source is :\n");
    for (int i = 0; i < n; ++i)
        printf("Distance of %d from %d is : %d\n", i, src, dist[i]);
}

// Function to find the vertex with minimum distance value from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int visited[], int n) {
    int min = INT_MAX, minIndex = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to implement Dijkstra's algorithm on a graph represented using adjacency list
void dijkstra(struct Graph* graph, int src) {
    int n = graph->V;
    int* visited = (int*)malloc(n * sizeof(int));
    int* dist = (int*)malloc(n * sizeof(int));

    // Initialize all distances as infinite and visited[] as false
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        dist[i] = INT_MAX;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        // u is always equal to src in the first iteration.
        int u = minDistance(dist, visited, n);

        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // Update dist[v] only if is not in visited[], there is an edge from u to v, and
            // the total weight of path from src to v through u is smaller than current value of dist[v]
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + pCrawl->weight < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
            }
            pCrawl = pCrawl->next;
        }
    }

    // Print the calculated distances
    printSolution(dist, n, src);

    // Free dynamically allocated memory
    free(visited);
    free(dist);
}

int main() {
    int src, dest;
    int n, edge;

    // Input the number of nodes and edges
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &edge);

    struct Graph* graph = createGraph(n);

    for (int i = 0; i < edge; i++) {
        int u, v, weight;
        printf("Enter the edge (u,v) and weight: ");
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(graph, u, v, weight);
    }

    printf("Enter source: ");
    scanf("%d", &src);

    dijkstra(graph, src);

    free(graph->array);
    free(graph);

    return 0;
}