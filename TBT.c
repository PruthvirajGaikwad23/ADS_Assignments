#include<stdio.h>
#include<stdlib.h>

typedef struct tbt_node
{
    int data,lbit,rbit;
    struct tbt_node *left,*right;
}tbt_node;

tbt_node* tbt_create(tbt_node*);
tbt_node* tbt_insert(tbt_node*,int);
void tbt_inorder(tbt_node*);
void tbt_preorder(tbt_node*);

void tbt_inorder(tbt_node *root)
{
    tbt_node *temp = root->left;
    while(temp->lbit == 1)
    temp = temp->left;
    while(temp != root)
    {
        printf("%d ",temp->data);
        if(temp->rbit == 0)
        temp = temp->right;
        else if(temp->rbit == 1)
        {
            temp = temp->right;
            while(temp->lbit == 1)
            temp = temp->left;
        }
    }
}

void tbt_preorder(tbt_node *root)
{
    tbt_node *temp = root->left;
    while (temp != root)
    {
        while (temp->lbit == 1)
        {
            printf("%d ", temp->data);
            temp = temp->left;
        }
        printf("%d ", temp->data);

        while (temp->rbit == 0 && temp->right != root)
        {
            temp = temp->right;
            if (temp == root)
                return;
        }

        temp = temp->right;
    }
}

tbt_node* tbt_create(tbt_node* root)
{
    int ch,n;
    do
    {
        printf("\n1)Add\n2)Exit");
        printf("\nEnter Choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\nEnter number");
                    scanf("%d",&n);
                    root = tbt_insert(root,n);
                    break;
            case 2: break;
            default:printf("\nWrong choice");
                    break;
        }
    }while(ch != 2);
    return root;
}

tbt_node* tbt_insert(tbt_node *root, int n)
{
    tbt_node *temp,*p;
    temp = (tbt_node*)malloc(sizeof(tbt_node));
    temp->data = n;
    temp->rbit = temp->lbit = 0;
    if(root->lbit == 0)
    {
        root->left = temp;
        root->lbit = 1;
        temp->left = temp->right = root;
        return root;
    }
    p = root->left;
    while(1)
    {
        if(n < p->data && p->lbit == 1)
        p = p->left;
        else if(n > p->data && p->rbit == 1)
        p = p->right;
        else
        break;
    }
    if(n < p->data)
    {
        temp->right = p;
        temp->left = p->left;
        p->left = temp;
        p->lbit = 1;
    }
    else
    {
        temp->left = p;
        temp->right = p->right;
        p->right = temp;
        p->rbit = 1;
    }
    return  root;
}

int main()
{
    int ch,n;
    tbt_node *root;
    root = (tbt_node*)malloc(sizeof(tbt_node));
    root->lbit = 0;
    root->right = root->left = root;
    root->rbit = 1;
    do
    {
        printf("\n\n1)Create\n2)Insert\n3)Inorder\n4)Preorder\n5)Exit");
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: root = tbt_create(root);
                    break;
            case 2: printf("\nEnter number");
                    scanf("%d",&n);
                    root = tbt_insert(root,n);
                    break;
            case 3: tbt_inorder(root);
                    break;
            case 4: tbt_preorder(root);
                    break;
            case 5: break;
            default:printf("\nWrong Choice");
                    break;
        }
    }while(ch != 5);
    return 0;
}