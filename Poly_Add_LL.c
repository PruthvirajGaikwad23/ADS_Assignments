#include<stdio.h>
#include<stdlib.h>

typedef struct poly
{
    int coeff;
    int exp;
    struct poly *next;
}poly;

poly* add(poly*,poly*);
void display(poly*);
poly* acceptPoly(int );

poly* acceptPoly(int n)
{
    poly *p,*head;
    p = head = (poly*)malloc(sizeof(poly));
    p->next = NULL;
    printf("\nEnter coefficient and expo :");
    scanf("%d%d",&p->coeff,&p->exp);
    for(int i=0;i<n-1;i++)
    {
        p->next = (poly*)malloc(sizeof(poly));
        p = p->next;
        p->next = NULL;
        printf("\nEnter coefficient and expo :");
        scanf("%d%d", &p->coeff,&p->exp);
    }
    printf("\n\n");
    return head;
}

poly* add(poly *p1,poly *p2)
{
    poly *p3,*head3;
    head3 = NULL;
    while(p1 != NULL && p2 != NULL)
    {
        if(head3 == NULL)
        {
            p3 = head3 = (poly*)malloc(sizeof(poly));
            p3->next = NULL;
        }
        else
        {
            p3->next = (poly*)malloc(sizeof(poly));
            p3 = p3->next;
            p3->next = NULL;
        }
        if(p1->exp == p2->exp)
        {
            p3->coeff = p1->coeff + p2->coeff;
            p3->exp = p1->exp;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->exp > p2->exp)
        {
            p3->exp = p1->exp;
            p3->coeff = p1->coeff;
            p1 = p1->next;
        }
        else
        {
            p3->exp = p2->exp;
            p3->coeff = p2->coeff;
            p2 = p2->next;
        }
    }
    while(p1 != NULL)
    {
        if(head3 == NULL)
        {
            p3 = head3 = (poly*)malloc(sizeof(poly));
            p3->next = NULL;
        }
        else
        {
            p3->next = (poly*)malloc(sizeof(poly));
            p3 = p3->next;
            p3->next = NULL;
        }
        p3->exp = p1->exp;
        p3->coeff = p1->coeff;
        p1 = p1->next;
        p3 = p3->next;
    }
    while(p2 != NULL)
    {
        if(head3 == NULL)
        {
            p3 = head3 = (poly*)malloc(sizeof(poly));
            p3->next = NULL;
        }
        else
        {
            p3->next = (poly*)malloc(sizeof(poly));
            p3 = p3->next;
            p3->next = NULL;
        }
        p3->exp = p2->exp;
        p3->coeff = p2->coeff;
        p2 = p2->next;
        p3 = p3->next;
    }
    return head3;
}

void display(poly *p)
{
    poly *temp;
    temp = p;
    while(temp != NULL)
    {
        if(temp->exp == 0)
        printf("%d",temp->coeff);
        else if(temp->next == NULL)
        printf("%dx^%d",temp->coeff,temp->exp);
        else
        printf("%dx^%d +",temp->coeff,temp->exp);
        temp = temp->next;
    }
}

int main()
{
    poly *p1,*p2,*p3;
    int n1,n2;
    printf("Enter number of terms in Polynomail-1 and Polynimail-2");
    scanf("%d%d",&n1,&n2);
    p1 = acceptPoly(n1);
    p2 = acceptPoly(n2);
    p3 = add(p1,p2);
    display(p3);
    return 0;
}