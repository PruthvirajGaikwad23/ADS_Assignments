#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* hashTable[N];

int hash(int key) {
    return key % N;
}

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insert(int key) {
    int index = hash(key);
    Node* newNode = createNode(key);

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        if (hash(hashTable[index]->key) != index) {
            // Replace and reinsert the displaced key
            Node* displacedNode = hashTable[index];
            hashTable[index] = newNode;
            insert(displacedNode->key);
            free(displacedNode); // Free the memory of displaced node
        } else {
            // Collision resolution using chaining
            int originalIndex = index;
            int i = 1;
            while (hashTable[(originalIndex + i) % N] != NULL && hashTable[(originalIndex + i) % N]->key != key) {
                index = (originalIndex + i) % N;
                i++;
            }
            if (hashTable[index] == NULL) {
                hashTable[index] = newNode;
            } else {
                Node* temp = hashTable[index];
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
    }
}

void display() {
    for (int i = 0; i < N; i++) {
        printf("Index %d: ", i);
        Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    // Initialize hash table with NULL values
    for (int i = 0; i < N; i++) {
        hashTable[i] = NULL;
    }

    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(15);
    insert(25);
    insert(35);
    insert(45);
    insert(55);
    insert(65);

    printf("Hash table entries are:\n");
    display();

    return 0;
}