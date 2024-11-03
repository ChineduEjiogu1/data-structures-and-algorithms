#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the Queue structure
struct Queue {
    int rear, front;
    int size;
    int *arr;
};

// Function to create a circular queue
struct Queue* createQueue(int s) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->size = s;
    q->front = q->rear = -1;
    q->arr = (int*)malloc(q->size * sizeof(int));
    return q;
}

// Function to insert an element into the circular queue
void enQueue(struct Queue* q, int value) {
    if ((q->front == 0 && q->rear == q->size - 1) || 
        ((q->rear + 1) % q->size == q->front)) {
        printf("\nQueue is Full");
        return;
    }
    else if (q->front == -1) { // Insert first element
        q->front = q->rear = 0;
        q->arr[q->rear] = value;
    }
    else if (q->rear == q->size - 1 && q->front != 0) {
        q->rear = 0;
        q->arr[q->rear] = value;
    }
    else {
        q->rear++;
        q->arr[q->rear] = value;
    }
}

// Function to delete an element from the circular queue
int deQueue(struct Queue* q) {
    if (q->front == -1) {
        printf("\nQueue is Empty");
        return INT_MIN;
    }
    int data = q->arr[q->front];
    q->arr[q->front] = -1;
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    else if (q->front == q->size - 1) {
        q->front = 0;
    }
    else {
        q->front++;
    }
    return data;
}

// Function to display the elements in the circular queue
void displayQueue(struct Queue* q) {
    if (q->front == -1) {
        printf("\nQueue is Empty");
        return;
    }
    printf("\nElements in Circular Queue are: ");
    if (q->rear >= q->front) {
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->arr[i]);
        }
    } else {
        for (int i = q->front; i < q->size; i++) {
            printf("%d ", q->arr[i]);
        }
        for (int i = 0; i <= q->rear; i++) {
            printf("%d ", q->arr[i]);
        }
    }
}

// Driver code to test the circular queue implementation
int main() {
    struct Queue* q = createQueue(5);

    // Inserting elements in Circular Queue
    enQueue(q, 14);
    enQueue(q, 22);
    enQueue(q, 13);
    enQueue(q, -6);

    // Display elements present in Circular Queue
    displayQueue(q);

    // Deleting elements from Circular Queue
    printf("\nDeleted value = %d", deQueue(q));
    printf("\nDeleted value = %d", deQueue(q));

    displayQueue(q);

    enQueue(q, 9);
    enQueue(q, 20);
    enQueue(q, 5);

    displayQueue(q);

    enQueue(q, 20); // This should show that the queue is full

    // Free allocated memory
    free(q->arr);
    free(q);

    return 0;
}
