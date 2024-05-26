#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Edge {
    int src, dest, weight;
};

struct AdjListNode {
    int dest, weight;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct GraphList {
    int numNodes;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct GraphList* createGraphList(int numNodes) {
    struct GraphList* graph = (struct GraphList*)malloc(sizeof(struct GraphList));
    graph->numNodes = numNodes;
    graph->array = (struct AdjList*)malloc(numNodes * sizeof(struct AdjList));
    for (int i = 0; i < numNodes; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(struct GraphList* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

struct Subset {
    int parent;
    int rank;
};

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compare(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}

void KruskalMST(struct GraphList* graph) {
    int numNodes = graph->numNodes;
    struct Edge result[numNodes];
    int e = 0;

    int i = 0;
    struct Edge* edges = (struct Edge*)malloc(numNodes * sizeof(struct Edge));
    for (int u = 0; u < numNodes; u++) {
        struct AdjListNode* temp = graph->array[u].head;
        while (temp != NULL) {
            if (temp->dest > u) {
                edges[i].src = u;
                edges[i].dest = temp->dest;
                edges[i].weight = temp->weight;
                i++;
            }
            temp = temp->next;
        }
    }
    qsort(edges, i, sizeof(edges[0]), compare);

    struct Subset* subsets = (struct Subset*)malloc(numNodes * sizeof(struct Subset));
    for (int v = 0; v < numNodes; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    i = 0;
    while (e < numNodes - 1 && i < numNodes) {
        struct Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    printf("Edge \tWeight\n");
    for (int j = 0; j < e; ++j)
        printf("%d - %d  ->%d \n", result[j].src, result[j].dest, result[j].weight);
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of vertices and edges in the graph: ");
    scanf("%d %d", &numNodes, &numEdges);

    struct GraphList* graph = createGraphList(numNodes);

    printf("Enter the edges (source node, destination node, weight):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }
    printf("\nMST\n");

    KruskalMST(graph);

    return 0;
}
