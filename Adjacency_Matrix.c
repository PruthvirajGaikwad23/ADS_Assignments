#include<stdio.h>
#include<stdlib.h>

int queue[50],front = -1,rear = -1;
int stack[50],top = -1;

void BFS(int [][10],int);
void DFS(int [][10],int);
void enqueue(int);
int dequeue();
int queue_empty();
void push(int);
int pop();
int stack_empty();

void push(int x)
{
    if(top == -1)
    {
        top++;
        stack[top] = x;
    }
    else
    {
        top++;
        stack[top] = x;
    }
}

int pop()
{
    if(top == -1)
    {
        printf("\nStack is empty");
        return -1;
    }
    else
    {
        int x = stack[top];
        top--;
        return x;
    }
}

int stack_empty()
{
    return (top == -1);
}

void enqueue(int x)
{
    if(front == -1 && rear == -1)
    {
        front++;
        rear++;
        queue[rear] = x;
    }
    else
    {
        rear++;
        queue[rear] = x;
    }
}

int dequeue()
{
    if(front == -1 && rear == -1)
    {
        printf("\nQueue is Empty");
        return -1;  // Return a value indicating an empty queue
    }
    else
    {
        int temp = queue[front];
        front++;
        if(front > rear)  // Reset queue if all elements are dequeued
        {
            front = rear = -1;
        }
        return temp;
    }
}

int queue_empty()
{
    return (front == -1 && rear == -1);
}

void BFS(int G[][10],int V)
{
    int visited[10],st,u;
    for(int i=0;i<V;i++)
        visited[i] = 0;
    printf("\nEnter starting vertex");
    scanf("%d",&st);
    visited[st] = 1;
    enqueue(st);
    while(!queue_empty())
    {
        u = dequeue();
        printf("%d ",u);
        for(int i=0;i<V;i++)
        {
            if(G[u][i] == 1 && visited[i] == 0)
            {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

void DFS(int G[][10],int V)
{
    int visited[10],u,st,i;
    for(i=0;i<V;i++)
        visited[i] = 0;
    printf("\nEnter starting vertex");
    scanf("%d",&st);
    push(st);
    printf("%d ",st);
    visited[st] = 1;
    u = st;
    while(!stack_empty())
    {
        for(i=0;i<V;i++)
        {
            if(G[u][i] == 1 && visited[i] == 0)
            {
                push(i);
                visited[i] = 1;
                printf("%d ",i);
                u = i;
                break;
            }
        }
        if(i == V)
        {
            pop();
            u = stack[top];
        }
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
    printf("\n\n1)BFS\n2)DFS");
    printf("\nEnter choice");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: BFS(G,V);
                break;
        case 2: DFS(G,V);
                break;
        default:printf("\nWrong Choice");
                break;
    }
    return 0;
}