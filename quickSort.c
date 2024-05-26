#include <stdio.h>

struct std
{
    int rno;
    char name[20];

} stdArray[10], temp;

void getStdArray(int studentSize)
{
    for (int i = 0; i < studentSize; i++)
    {
        printf("ENTER ROLL NO.\n");
        scanf("%d", &stdArray[i].rno);
        printf("ENTER NAME.\n");
        scanf("%s", stdArray[i].name);
    }
}

void swap(int i, int largest)
{

    temp = stdArray[i];
    stdArray[i] = stdArray[largest];
    stdArray[largest] = temp;
}
void printStdArray(int studentSize)
{
    for (int i = 0; i < studentSize; i++)
    {
        printf("%d- %s\n", stdArray[i].rno, stdArray[i].name);
    }
}

int partition( int low, int high)
{
    int pivot = stdArray[low].rno;
    int st = low;
    int end = high;
    int k = high;
    for (int i = high; i > low; i--) {
        if (stdArray[i].rno > pivot)
            swap(i, k--);
    }
    swap(low, k);
    return k;
}
void quickSort( int low, int high)
{
    if (low < high) {

        int idx = partition( low, high);
 
        quickSort( low, idx - 1);
        quickSort( idx + 1, high);
    }
}
int main()
{
    int studentSize;
    printf("ENTER THE NUMBER OF STUDENT(<10)\n");
    scanf("%d", &studentSize);
    getStdArray(studentSize);
    quickSort(0,studentSize-1);
    printStdArray(studentSize);
    return 0;
}

