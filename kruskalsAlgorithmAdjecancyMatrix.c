#include <stdio.h>
#include <stdlib.h>

#define m 10

struct Graph
{
    int matrix[m][m];
    int V;
};

void init(struct Graph *g, int v)
{
    g->V = v;
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
            g->matrix[i][j] = 999;
    }
}

void addEdgesMatrix(struct Graph *g, int a, int b,int k)
{
    if (a >= 0 && a < g->V && b >= 0 && b < g->V)
    {
        g->matrix[a][b] = k;
        g->matrix[b][a] = k;
    }
    else
    {
        printf("Invalid node indices!\n");
    }
}


int parent[m];

int findparent(int i) {
    while (parent[i] != i) {
        i = parent[i];
    }
    return i;
}

void union1(int i, int j) {
    int a = findparent(i);
    int b = findparent(j);
    parent[a] = b;
}

void KruskalMatrix(struct Graph* g) {
    int min = 999, n = 1, a, b;
    int minweight = 0;

    for (int i = 0; i < g->V; i++) {
        parent[i] = i;
    }

    while (n < g->V ) { 
        min = 999;
        for (int i = 0; i < g->V; i++) {
            for (int j = 0; j < g->V; j++) {
                if (g->matrix[i][j] < min && findparent(i) != findparent(j)) {
                    a = i;
                    b = j;
                    min = g->matrix[i][j];
                }
            }
        }

        union1(a, b);
        printf("%d %d \t-> %d\n", a, b, min);
        minweight = minweight + min;
        n++;
    }
    //  printf("Weight of MST: %d\n", minweight);
}

void Print(struct Graph *g)
{
   
    for (int i = 0; i < g->V; i++)
    {
        for (int j = 0; j < g->V; j++)
        {
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");
    }
}



int main() {
     struct Graph *g =  (struct Graph *)malloc(sizeof(struct Graph));
     int v,a,b,w,e,ch;
    printf("No. of Vertices: ");
    scanf("%d", &v);
    init(g,v);
    printf("No. of Edges: ");
    scanf("%d", &e);

    printf("Enter Edge (src,dest,weight):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &a, &b, &w);
        addEdgesMatrix(g,a,b,w);
    }
     printf("\nMST\n");
        KruskalMatrix(g);
    return 0;
}