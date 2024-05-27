//using matrix

#include <stdio.h>
#include <stdlib.h>

#define m 20

struct Graph {
    int V;
    int matrix[m][m];
};

void DijkstraAlgo(int G[][m], int ver);

int min_dist(int dist[], int visited[], int ver);

void display(int dist[], int ver);

int main() {
    int G[m][m], ver, edge, i, j, v, u;

    printf("Enter no. of Vertex: ");
    scanf("%d", &ver);

    for (int i = 0; i < ver; i++) {
        for (j = 0; j < ver; j++) {
            G[i][j] = 999;
        }
    }

    printf("Enter No. of Edges: ");
    scanf("%d", &edge);

    for (i = 0; i < edge; i++) {
        printf("Enter Edge (u v): ");
        scanf("%d %d", &u, &v);
        printf("Enter Weight: ");
        scanf("%d", &G[u][v]);
    }

    printf("Adjacency Matrix:\n");
    for (i = 0; i < ver; i++) {
        for (j = 0; j < ver; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    DijkstraAlgo(G, ver);
    return 0;
}

void DijkstraAlgo(int G[][m], int ver) {
    int dist[m], visited[m];
    int src, i, u;
    for (int i = 0; i < ver; i++) {
        dist[i] = 999;
        visited[i] = 0;
    }
    printf("Enter Source Vertex: ");
    scanf("%d", &src);
    dist[src] = 0;

    for (int i = 0; i < ver - 1; i++) {
        u = min_dist(dist, visited, ver);
        visited[u] = 1;
        for (int j = 0; j < ver; j++) {
            if (visited[j] != 1 && G[u][j] && dist[u] != 999 && dist[u] + G[u][j] < dist[j]) {
                dist[j] = dist[u] + G[u][j];
            }
        }
    }
    display(dist, ver);
}

int min_dist(int dist[], int visited[], int ver) {
    int min = 999, index;
    for (int i = 0; i < ver; i++) {
        if (visited[i] != 1 && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void display(int dist[], int ver) {
    printf("Vertex \t Distance from Source: \n");
    for (int i = 0; i < ver; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}