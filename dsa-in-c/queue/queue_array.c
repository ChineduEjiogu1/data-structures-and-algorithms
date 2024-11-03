#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front, rear, capacity;
    int* queue;
};

// Function to initialize the queue
struct Queue* createQueue(int capacity) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->queue = (int*)malloc(q->capacity * sizeof(int));
    return q;
}

// Function to insert an element at the rear of the queue
void enqueue(struct Queue* q, int data) {
    // Check if the queue is full
    if (q->rear == q->capacity - 1) {
        printf("Queue is full\n");
        return;
    }

    // Insert element at the rear
    q->queue[++q->rear] = data;
}

// Function to delete an element from the front of the queue
void dequeue(struct Queue* q) {
    // If the queue is empty
    if (q->front > q->rear) {
        printf("Queue is empty\n");
        return;
    }

    // Shift all elements from index 1 till rear to the left by one
    for (int i = 0; i < q->rear; i++) {
        q->queue[i] = q->queue[i + 1];
    }

    // Decrement rear
    q->rear--;
}

// Function to print queue elements
void display(struct Queue* q) {
    if (q->front > q->rear) {
        printf("Queue is Empty\n");
        return;
    }

    // Traverse front to rear and print elements
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d <-- ", q->queue[i]);
    }
    printf("\n");
}

// Function to print the front of the queue
void front(struct Queue* q) {
    if (q->rear == -1) {
        printf("Queue is Empty\n");
        return;
    }
    printf("Front Element is: %d\n", q->queue[q->front]);
}

// Driver code
int main() {
    // Create a queue of capacity 4
    struct Queue* q = createQueue(4);

    // Print queue elements
    display(q);

    // Insert elements in the queue
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    enqueue(q, 50);

    // Print queue elements
    display(q);

    // Insert element in the queue
    enqueue(q, 60);

    // Print queue elements
    display(q);

    // Dequeue elements
    dequeue(q);
    dequeue(q);

    printf("After two node deletions\n");

    // Print queue elements
    display(q);

    printf("After one insertion\n");
    enqueue(q, 60);

    // Print queue elements
    display(q);

    // Print front of the queue
    front(q);

    // Free the allocated memory
    free(q->queue);
    free(q);

    return 0;
}