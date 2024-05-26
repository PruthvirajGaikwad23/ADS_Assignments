// C Program for HeapSort 
#include <stdio.h> 

struct std
{
    int rno;
    char name[20];

} stdArr[10], temp;

void create_max_heap(int n, int i) 
{ 
    int maximum, left_index, right_index; 

    maximum = i; 

    right_index = 2 * i + 2; 

    left_index = 2 * i + 1; 

    if (left_index < n && stdArr[left_index].rno > stdArr[maximum].rno) 
        maximum = left_index; 

    if (right_index < n && stdArr[right_index].rno > stdArr[maximum].rno) 
        maximum = right_index; 

    if (maximum != i) { 
        temp = stdArr[i]; 
        stdArr[i] = stdArr[maximum]; 
        stdArr[maximum] = temp; 
        create_max_heap(n, maximum); 
    } 
} 

void heapsort (int n) 
{ 
    int i; 
    for (i = n / 2 - 1; i >= 0; i--) { 
        create_max_heap(n, i); 
    } 

    for (i = n - 1; i > 0; i--) { 
        temp = stdArr[0]; 
        stdArr[0] = stdArr[i]; 
        stdArr[i] = temp; 
        create_max_heap(i, 0); 
    } 
} 

void getStudent(int size)
{
    for(int i=0;i<size;i++)
    {
        printf("\nEnter your Roll Number and Name\n");
        scanf("%d%s",&stdArr[i].rno, stdArr[i].name);
    }
}

void display(int size)
{
    for(int i=0;i<size;i++)
    {
        printf("\n%d - %s",stdArr[i].rno, stdArr[i].name);
    }
}

int main() 
{ 
    int studentNo;
    printf("Enter number of students\n");
    scanf("%d",&studentNo);
    getStudent(studentNo);
    heapsort(studentNo);
    display(studentNo);

    return 0; 
}
