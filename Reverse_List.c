#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node* reverse(node*);
node* create(node*);
node* insert(node*,int);
void display(node *);

node* create(node *root)
{
    int ch,n;
    do
    {
        printf("\n1)Add\n2)Exit");
        printf("\n\nEnter choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\nEnter number");
                    scanf("%d",&n);
                    root = insert(root,n);
                    break;
            case 2: break;
            default:printf("\nWrong Input");
                    break;
        }
    }while(ch != 2);
    return root;
}

node* insert(node *root, int n)
{
    node *temp;
    temp = root;
    if(root == NULL)
    {
        root = (node*)malloc(sizeof(node));
        root->data = n;
        root->next = NULL;
        return root;
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (node*)malloc(sizeof(node));
        temp = temp->next;
        temp->data = n;
        temp->next = NULL;
    }
    return root;
}

node* reverse(node *root)
{
    node *head,*curr = root,*prev = NULL,*next = NULL;
    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

void display(node *root)
{
    node *temp = root;
    while(temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
}

int main()
{
    node *root = NULL;
    int ch,n;
    do
    {
        printf("\n1)Create\n2)Insert\n3)Reverse\n4)Display\n5)Exit");
        printf("\nEnter choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: root = create(root);
                    break;
            case 2: printf("\n\nEnter Number");
                    break;
            case 3: root = reverse(root);
                    break;
            case 4: display(root);
                    break;
            case 5: break;
            default:printf("\n\nWrong choice");
                    break;
        }
    }while(ch != 5);
    free(root);
    return 0;
}