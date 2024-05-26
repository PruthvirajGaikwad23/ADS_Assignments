#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_int 100

struct Node {
    int data;
    int weight;
    struct Node* next;
};

struct Graph {
    struct Node* array[MAX_int];
};

int minDist(int dist[], bool visit[], int number) {
    int min = 999, min_index;
    for (int v=0; v<number; v++) {
        if (!visit[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int num, int G[MAX_int][MAX_int]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < num; i++)
        printf("%d - %d \t%d \n", parent[i], i, G[i][parent[i]]);
}

void primMSTMatrix(int G[MAX_int][MAX_int], int num) {
    int parent[MAX_int];
    int dist[MAX_int];
    bool visit[MAX_int];

    for (int i=0; i<num; i++) {
        dist[i] = 999;
        visit[i] = false;
        parent[i] = -1;
    }

    dist[0] = 0;

    for (int count=0; count<num-1; count++) {

        int u = minDist(dist, visit, num);

        visit[u] = true;

        for (int v=0; v<num; v++) {
            if (G[u][v] && !visit[v] && G[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = G[u][v];
            }
        }
    }

    printMST(parent, num, G);
}

void primMSTList(struct Graph* graph, int num) {
    int parent[MAX_int];
    int dist[MAX_int];
    bool visit[MAX_int];

    for (int i=0; i<num; i++) {
        dist[i] = 999;
        visit[i] = false;
        parent[i] = -1;
    }

    dist[0] = 0;

    for (int count=0; count<num-1; count++) {
        int u = minDist(dist, visit, num);
        visit[u] = true;

        struct Node* temp = graph -> array[u];
        while (temp != NULL) {
            int v = temp -> data;
            if (!visit[v] && temp -> weight < dist[v]) {
                parent[v] = u;
                dist[v] = temp -> weight;
            }
            temp = temp->next;
        }
    }

    printf("Edge \tWeight\n");
    for (int i=1; i<num; i++) {
        printf("%d - %d \t%d \n", parent[i], i, dist[i]);
    }
}

struct Node* createNode(int data, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode -> data = data;
    newNode -> weight = weight;
    newNode -> next = NULL;
    return newNode;
}

struct Graph* createGraph(int num) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    for (int i=0; i<num; i++)
        graph -> array[i] = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode -> next = graph -> array[src];
    graph -> array[src] = newNode;

    newNode = createNode(src, weight);
    newNode -> next = graph -> array[dest];
    graph -> array[dest] = newNode;
}

int main() {
    int num, edges;
    printf("Enter the number of nodes and edges in the graph: ");
    scanf("%d %d", &num, &edges);

    int G[MAX_int][MAX_int] = {0};
    struct Graph* graph = createGraph(num);

    printf("Enter the edges:\n");
    for (int i=0; i<edges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        G[src][dest] = G[dest][src] = weight;
        addEdge(graph, src, dest, weight);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Prim's using matrix\n");
        printf("2. Prim's using list\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Minimum Spanning Tree using adjacency matrix:\n");
                primMSTMatrix(G, num);
                break;
            case 2:
                printf("Minimum Spanning Tree using adjacency list:\n");
                primMSTList(graph, num);
                break;
            case 3:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    return 0;
}