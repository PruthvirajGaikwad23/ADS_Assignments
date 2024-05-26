#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int size;
} queue;

// Initialize the queue
void initqueue(queue* q) {
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

// Check if the queue is full
int isFull(queue* q) {
    return q->size == MAX;
}

// Check if the queue is empty
int isEmpty(queue* q) {
    return q->size == 0;
}

// Insert element at the front
void insertFront(queue* q, int value) {
    if (isFull(q)) {
        printf("queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->front = (q->front - 1 + MAX) % MAX;
    }
    q->arr[q->front] = value;
    q->size++;
}

// Insert element at the rear
void insertRear(queue* q, int value) {
    if (isFull(q)) {
        printf("queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->arr[q->rear] = value;
    q->size++;
}

// Delete element from the front
int deleteFront(queue* q) {
    if (isEmpty(q)) {
        printf("queue is empty\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    q->size--;
    return value;
}

// Delete element from the rear
int deleteRear(queue* q) {
    if (isEmpty(q)) {
        printf("queue is empty\n");
        return -1;
    }
    int value = q->arr[q->rear];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->rear = (q->rear - 1 + MAX) % MAX;
    }
    q->size--;
    return value;
}

// Display the queue
void displayqueue(queue* q) {
    if (isEmpty(q)) {
        printf("queue is empty\n");
        return;
    }
    printf("queue elements: ");
    int i = q->front;
    for (int count = 0; count < q->size; count++) {
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    queue q;
    initqueue(&q);

    int choice, value;
    while (1) {
        printf("\n1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n5. Display queue\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(&q, value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(&q, value);
                break;
            case 3:
                value = deleteFront(&q);
                if (value != -1) {
                    printf("Deleted from front: %d\n", value);
                }
                break;
            case 4:
                value = deleteRear(&q);
                if (value != -1) {
                    printf("Deleted from rear: %d\n", value);
                }
                break;
            case 5:
                displayqueue(&q);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
