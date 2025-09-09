#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

void enqueue(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    if (front == NULL) {
        front = rear = newNode;
        rear->next = front; 
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
    printf("Inserted %d\n", value);
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is Empty!\n");
        return;
    }
    if (front == rear) {  
        printf("Deleted %d\n", front->data);
        free(front);
        front = rear = NULL;
    } else {
        struct Node *temp = front;
        printf("Deleted %d\n", front->data);
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

void display() {
    if (front == NULL) {
        printf("Queue is Empty!\n");
        return;
    }
    struct Node *temp = front;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    display();
    enqueue(40);
    enqueue(50);
    display();
    return 0;
}
