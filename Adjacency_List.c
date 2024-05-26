#include<stdio.h>
#include<stdlib.h>

int queue[50],front = -1,rear = -1;
int stack[50],top = -1;

typedef struct node
{
    int vertex;
    struct node *next;
}node;

node *A[10];

void BFS(node* [],int);
void DFS(node* [],int);
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

void BFS(node *A[],int V)
{
    node *p;
    int visited[10],st,u;
    for(int i=0;i<V;i++)
        visited[i] = 0;
    printf("\nEnter Starting vertex");
    scanf("%d",&st);
    visited[st] = 1;
    enqueue(st);
    while(!queue_empty())
    {
        u = dequeue();
        printf("%d ",u);
        p = A[u];
        while(p !=NULL)
        {
            if(visited[p->vertex] == 0)
            {
                enqueue(p->vertex);
                visited[p->vertex] = 1;
            }
            p = p->next;
        }
    }
}

void DFS(node *A[],int V)
{
    int visited[10],u,st;
    node *p;
    for(int i=0;i<V;i++)
        visited[i] = 0;
    printf("\nEnter starting vertex");
    scanf("%d",&st);
    visited[st] = 1;
    push(st);
    printf("%d",st);
    p = A[u];
    while(!stack_empty())
    {
        p = A[u];
        while(p != NULL)
        {
            if(visited[p->vertex] == 0)
            {
                push(p->vertex);
                visited[p->vertex] = 1;
                printf("%d ",p->vertex);
                u = p->vertex;
                break;
            }
            else
            {
                p = p->next;
            }
            if(p == NULL)
            {
                pop();
                u = stack[top];
            }
        }
    }
}

int main()
{
    char ch = 'y';
    node *p,*newu,*newv;
    int V,u,v;
    printf("\nEnter number of vertex: ");
    scanf("%d",&V);
    for(int i=0;i<V;i++)
        A[i] = NULL;
    do
    {
        printf("\nEnter edge");
        scanf("%d%d",&u,&v);
        newu = (node*)malloc(sizeof(node));
        newu->vertex = v;
        newu->next = NULL;
        p = A[u];
        if(p == NULL)
            A[u] = newu;
        else
        {
            while(p->next != NULL)
                p = p->next;
            p->next = newu;
        }
        newv = (node*)malloc(sizeof(node));
        newv->vertex = u;
        newv->next = NULL;
        p = A[v];
        if(p == NULL)
            A[v] = newu;
        else
        {
            while(p->next != NULL)
                p = p->next;
            p->next = newv;
        }
        printf("\nAdd more edges (y/n)");
        scanf("%c",&ch);
    }while(ch == 'y');
    do 
    {
        printf("\n\n1)BFS\n2)DFS\n3)Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: BFS(A,V);
                    break;
            case 2: DFS(A,V);
                    break;
            case 3: break;
            default:printf("\nWrong input");
                    break;
        }
    }while(ch != 3);
    return 0;
}