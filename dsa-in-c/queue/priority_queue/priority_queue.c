#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 100
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

/* ===== MinHeap Structure and Functions ===== */
typedef struct {
    int *heap;
    int size;
    int capacity;
} MinHeap;

// Initialize the MinHeap
MinHeap* createMinHeap() {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->heap = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    h->size = 0;
    h->capacity = INITIAL_CAPACITY;
    return h;
}

// Resize the heap array if needed
void resizeMinHeap(MinHeap *h) {
    if (h->size >= h->capacity) {
        h->capacity *= 2;
        h->heap = (int *)realloc(h->heap, h->capacity * sizeof(int));
    }
}

// Sift up to maintain heap property after insertion
void minHeapSiftUp(MinHeap *h, int i) {
    while (i > 0 && h->heap[i] < h->heap[PARENT(i)]) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[PARENT(i)];
        h->heap[PARENT(i)] = temp;
        i = PARENT(i);
    }
}

// Sift down to maintain heap property after extraction
void minHeapSiftDown(MinHeap *h, int i) {
    int smallest = i;
    int left = LEFT(i);
    int right = RIGHT(i);

    if (left < h->size && h->heap[left] < h->heap[smallest]) {
        smallest = left;
    }
    if (right < h->size && h->heap[right] < h->heap[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[smallest];
        h->heap[smallest] = temp;
        minHeapSiftDown(h, smallest);
    }
}

// Insert an element into the MinHeap
void minHeapInsert(MinHeap *h, int element) {
    resizeMinHeap(h);
    h->heap[h->size] = element;
    minHeapSiftUp(h, h->size);
    h->size++;
}

// Extract the minimum element
int minHeapExtractMin(MinHeap *h) {
    if (h->size == 0) {
        printf("Heap is empty!\n");
        return -1; // Or INT_MAX as a sentinel value
    }
    int min = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    minHeapSiftDown(h, 0);
    return min;
}

/* ===== MaxHeap Structure and Functions ===== */
typedef struct {
    int *heap;
    int size;
    int capacity;
} MaxHeap;

// Initialize the MaxHeap
MaxHeap* createMaxHeap() {
    MaxHeap *h = (MaxHeap *)malloc(sizeof(MaxHeap));
    h->heap = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    h->size = 0;
    h->capacity = INITIAL_CAPACITY;
    return h;
}

// Resize the heap array if needed
void resizeMaxHeap(MaxHeap *h) {
    if (h->size >= h->capacity) {
        h->capacity *= 2;
        h->heap = (int *)realloc(h->heap, h->capacity * sizeof(int));
    }
}

// Sift up to maintain heap property after insertion
void maxHeapSiftUp(MaxHeap *h, int i) {
    while (i > 0 && h->heap[i] > h->heap[PARENT(i)]) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[PARENT(i)];
        h->heap[PARENT(i)] = temp;
        i = PARENT(i);
    }
}

// Sift down to maintain heap property after extraction
void maxHeapSiftDown(MaxHeap *h, int i) {
    int largest = i;
    int left = LEFT(i);
    int right = RIGHT(i);

    if (left < h->size && h->heap[left] > h->heap[largest]) {
        largest = left;
    }
    if (right < h->size && h->heap[right] > h->heap[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[largest];
        h->heap[largest] = temp;
        maxHeapSiftDown(h, largest);
    }
}

// Insert an element into the MaxHeap
void maxHeapInsert(MaxHeap *h, int element) {
    resizeMaxHeap(h);
    h->heap[h->size] = element;
    maxHeapSiftUp(h, h->size);
    h->size++;
}

// Extract the maximum element
int maxHeapExtractMax(MaxHeap *h) {
    if (h->size == 0) {
        printf("Heap is empty!\n");
        return -1; // Or INT_MIN as a sentinel value
    }
    int max = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    maxHeapSiftDown(h, 0);
    return max;
}

/* ===== PriorityQueue Using MaxHeap ===== */
typedef struct {
    MaxHeap *queue;
} PriorityQueue;

// Initialize the PriorityQueue
PriorityQueue* createPriorityQueue() {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->queue = createMaxHeap();
    return pq;
}

// Enqueue an element
void priorityQueueEnqueue(PriorityQueue *pq, int element) {
    maxHeapInsert(pq->queue, element);
}

// Dequeue the highest priority element
int priorityQueueDequeue(PriorityQueue *pq) {
    return maxHeapExtractMax(pq->queue);
}

// Get the highest priority element without removing it
int priorityQueuePeek(PriorityQueue *pq) {
    if (pq->queue->size == 0) {
        printf("Priority Queue is empty!\n");
        return -1;
    }
    return pq->queue->heap[0];
}

// Check if the queue is empty
bool priorityQueueIsEmpty(PriorityQueue *pq) {
    return pq->queue->size == 0;
}

/* ===== Example Usage ===== */
int main() {
    PriorityQueue *pq = createPriorityQueue();

    priorityQueueEnqueue(pq, 10);
    priorityQueueEnqueue(pq, 30);
    priorityQueueEnqueue(pq, 20);

    printf("Top Priority: %d\n", priorityQueuePeek(pq));
    printf("Dequeued: %d\n", priorityQueueDequeue(pq));
    printf("Top Priority After Dequeue: %d\n", priorityQueuePeek(pq));

    return 0;
}
