#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *left, *right;
}node;

typedef struct stack
{
    node *T;
    struct stack *next;
}stack;

typedef struct queue
{
    node *T;
    struct queue *next;
}queue;

node* create(node *);
node* insert(node*,int);
void inorder(node*);
void preorder(node*);
void postorder(node*);
int height(node*);
node* delete(node*,int);
node* findmin(node*);
void push(node *, stack**);
node* pop(stack**);
int empty_stack(stack *);
node* top_stack(stack **);
void stack_inorder(node*);
void stack_preorder(node*);
void stack_postorder(node*);
void mirror(node*);
void enqueue(node*,queue**);
node* dequeue(queue**);
void level_BST(node*);
int empty_queue(queue *); 

void level_BST(node *root)
{
    if (root == NULL)
        return;
    queue (*top_q) = NULL;
    enqueue(root, &top_q);
    while (!empty_queue(top_q))
    {
        root = dequeue(&top_q);
        printf("%d ", root->data);
        if (root->left != NULL)
            enqueue(root->left, &top_q);
        if (root->right != NULL)
            enqueue(root->right, &top_q);
    }
}

int empty_queue(queue *top_q)
{
    if(top_q == NULL) 
    return 1;
    return 0;
}

void enqueue(node *root, queue **top_q)
{
    queue *temp = (queue*)malloc(sizeof(queue));
    temp->T = root;
    temp->next = NULL;
    if ((*top_q) == NULL)
    {
        (*top_q) = temp;
    }
    else
    {
        queue *current = (*top_q);
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = temp;
    }
}

node* dequeue(queue **top_q)
{
    if ((*top_q) == NULL)
        return NULL;
    queue *temp = (*top_q);
    (*top_q) = (*top_q)->next;
    node *n = temp->T;
    free(temp);
    return n;
}

void mirror(node *root)
{
    stack *top = NULL;
    node *temp,*p;
    p = root;
    push(p,&top);
    while(!empty_stack(top))
    {
        p = pop(&top);
        temp = p->left;
        p->left = p->right;
        p->right = temp;
        if(p->right != NULL)
            push(p->right,&top);
        else if(p->left != NULL)
            push(p->left,&top);
    }
    printf("\nMirror image = ");
    stack_inorder(root);
}

void push(node *root,stack **top)
{
    stack *temp = (stack*)malloc(sizeof(stack));
    temp->T = root;
    temp->next = (*top);
    (*top) = temp;
}

node* pop(stack **top)
{
    stack *temp;
    node *n;
    temp = (*top);
    (*top) = (*top)->next;
    n = temp->T;
    free(temp);
    return n;
}

int empty_stack(stack *top)
{
    if(top == NULL) 
    return 1;
    return 0;
}

node* top_stack(stack **top)
{
    return ((*top)->T);
}

void stack_inorder(node *root)
{
    stack *top = NULL;
    while(root != NULL)
    {
        push(root,&top);
        root = root->left;
    }
    while(!empty_stack(top))
    {
        root = pop(&top);
        printf("%d ",root->data);
        root = root->right;
        while(root != NULL)
        {
            push(root,&top);
            root = root->left;
        }
    }
}

void stack_preorder(node* root)
{
    stack *top = NULL;
    while(root != NULL)
    {
        printf("%d ",root->data);
        push(root,&top);
        root = root->left;
    }
    while(!empty_stack(top))
    {
        root = pop(&top);
        root = root->right;
        while(root != NULL)
        {
            printf("%d ",root->data);
            push(root,&top);
            root = root->left;
        }
    }
}

void stack_postorder(node *root)
 {   
    if(root == NULL)
        return;
    node *prev = NULL;
    stack *top = NULL;
    node *T = root;
    
    do {	
        while (T != NULL) {
            push(T, &top);
            T = T -> left;
        }

        while (T == NULL && !empty_stack(top)) {
            T = top_stack(&top);

            if (T -> right == NULL || T -> right == prev) {
                printf("%d ", T -> data);
                pop(&top);
                prev = T;
                T = NULL; 
            } else {
                T = T -> right;
            }
        }
    } while (!empty_stack(top));
}

node* delete(node *root, int n)
{
    node *temp;
    if(root == NULL)
    {
        return root;
    }
    else if(n > root->data)
        root->right = delete(root->right,n);
    else if(n < root->data)
        root->left = delete(root->left,n);
    else
    {
        if(root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }
        else if(root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else
        {
            temp = findmin(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}

node* findmin(node *root)
{
    node* temp = root;
    while(temp->left != NULL)
        temp = temp->left;
    return temp;
}

node* create(node *root)
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
                    root = insert(root,n);
                    break;
            case 2: break;
            default:printf("\nWrong choice");
                    break;
        }
    }while(ch != 2);
    return root;
}

node* insert(node *root, int n)
{
    if(root == NULL)
    {
        root = (node*)malloc(sizeof(node));
        root->data = n;
        root->right = NULL;
        root->left = NULL;
        return root;
    }
    else if(n>root->data)
    {
        root->right = insert(root->right,n);
    }
    else
    {
        root->left = insert(root->left,n);
    }
    return root;
}

void inorder(node *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void preorder(node *root)
{
    if(root != NULL)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node *root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

int height(node *root)
{
    if(root == NULL)
    {
        return -1; // Return -1 to denote that empty tree has height -1
    }
    else
    {
        int left_height = height(root->left);
        int right_height = height(root->right);
        return (left_height > right_height ? left_height : right_height) + 1;
    }
}

int main()
{
    node *root = NULL;
    int ch,n;
    do
    {
        printf("\n\n1)Create\n2)Insert\n3)Inorder\n4)Preorder\n5)Postorder\n6)Height\n7)Delete\n8)Non-Recursive Inorder\n9)Non-Recursive Preorder\n10)Non-Recursive Postorder\n11)Mirror\n12)Level_BST\n13)Exit\n");
        printf("\nEnter Choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: root = create(root);
                    break;
            case 2: printf("\n\nEnter data");
                    scanf("%d",&n);
                    root = insert(root,n);
                    break;
            case 3: inorder(root);
                    break; 
            case 4: preorder(root);
                    break;
            case 5: postorder(root);
                    break;
            case 6: printf("\nHeight= %d",height(root));
                    break;
            case 7: printf("\nEnter node to be deleted: ");
                    scanf("%d",&n);
                    root = delete(root,n);
                    break;
            case 8: stack_inorder(root);
                    break;
            case 9: stack_preorder(root);
                    break;
            case 10:stack_postorder(root);
                    break;
            case 11:mirror(root);
                    break;
            case 12:level_BST(root);
                    break;
            case 13:break;
            default:printf("\nwrong choice");
                    break;
        }
    }while(ch!=12);
    return 0;
}

