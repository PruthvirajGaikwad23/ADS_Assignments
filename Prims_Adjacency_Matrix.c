#include<stdio.h>
#include<stdlib.h>

void prims(int [][10],int);
int FindMinDist(int [],int [],int);
void DisplayMST(int [],int [][10],int);

void prims(int G[][10],int V)
{
    int visited[10],distance[10],parent[10],u;
    for(int i=0;i<V;i++)
    {
        visited[i] = 0;
        distance[i] = 999;
        parent[i] = -1;
    }
    distance[0] = 0;
    for(int i=0;i<(V-1);i++)
    {
        i = FindMinDist(distance,visited,V);
        visited[u] = 1;
        for(int j=0;j<V;j++)
        {
            if(G[u][j] != 999 && visited[j] == 0 && distance[j]>G[u][j])
            {
                distance[j] = G[u][j];
                parent[j] = u;
            }
        }
    }
    DisplayMST(parent,G,V);
}

int FindMinDist(int distance[], int visited[],int V)
{
    int index,min = 999;
    for(int i=0;i<V;i++)
    {
        if(visited[i] == 0 && distance[i]<min)
        {
            min = distance[i];
            index = i;
        }
    }
    return index;
}

void DisplayMST(int parent[],int G[][10],int V)
{
    printf("\nPrim's MST, Edge \t weight\n");
    for(int i=0;i<V;i++)
    {
        printf("Edge: %d %d, weight:- %d",i,parent[i],G[i][parent[i]]);
    }
}

int main()
{
    int G[10][10],V,e,u,v,ch;
    printf("Enter number of vertex");
    scanf("%d",&V);
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
            G[i][j] = 0;
    }
    printf("\nEnter number of edges");
    scanf("%d",&e);
    for(int i=0;i<e;i++)
    {
        printf("\nEnter Edge: ");
        scanf("%d%d",&u,&v);
        G[u][v] = G[v][u] = 1;
    }
    prims(G,V);
    return 0;
}