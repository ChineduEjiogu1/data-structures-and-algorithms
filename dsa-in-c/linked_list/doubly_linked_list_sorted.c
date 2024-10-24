#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
} DoublyLinkedList;

Node* create_node(void* data, size_t data_size) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    new_node->next = new_node->prev = NULL;
    return new_node;
}

DoublyLinkedList* create_list() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list->head = list->tail = NULL;
    return list;
}

int is_empty(DoublyLinkedList* list) {
    return list->head == NULL;
}

void insert_front(DoublyLinkedList* list, void* data, size_t data_size) {
    Node* new_node = create_node(data, data_size);
    if (is_empty(list)) {
        list->head = list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
}

void insert_back(DoublyLinkedList* list, void* data, size_t data_size) {
    Node* new_node = create_node(data, data_size);
    if (is_empty(list)) {
        list->head = list->tail = new_node;
    } else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void traverse_forward(DoublyLinkedList* list, void (*func)(void*)) {
    for (Node* current = list->head; current; current = current->next)
        func(current->data);
}

void traverse_backward(DoublyLinkedList* list, void (*func)(void*)) {
    for (Node* current = list->tail; current; current = current->prev)
        func(current->data);
}

Node* search(DoublyLinkedList* list, void* target, int (*cmp)(void*, void*)) {
    for (Node* current = list->head; current; current = current->next)
        if (cmp(current->data, target) == 0)
            return current;
    return NULL;
}

void delete_node(DoublyLinkedList* list, void* target, int (*cmp)(void*, void*)) {
    for (Node* current = list->head; current; current = current->next) {
        if (cmp(current->data, target) == 0) {
            if (current->prev)
                current->prev->next = current->next;
            else
                list->head = current->next;

            if (current->next)
                current->next->prev = current->prev;
            else
                list->tail = current->prev;

            free(current->data);
            free(current);
            return;
        }
    }
}

void* delete_front(DoublyLinkedList* list) {
    if (is_empty(list)) return NULL;
    Node* to_delete = list->head;
    list->head = list->head->next;
    if (list->head)
        list->head->prev = NULL;
    else
        list->tail = NULL;
    
    void* data = to_delete->data;
    free(to_delete);  // Free the node, but not the data.
    return data;
}

void print_int(void* data) {
    printf("%d ", *(int*)data);
}

int compare_int(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

// Bubble Sort algorithm for the Doubly Linked List
void bubble_sort(DoublyLinkedList* list, int (*cmp)(void*, void*)) {
    if (is_empty(list) || list->head->next == NULL) return;  // List is empty or has only one element

    int swapped;
    Node *ptr, *last_ptr = NULL;

    do {
        swapped = 0;
        ptr = list->head;

        while (ptr->next != last_ptr) {
            if (cmp(ptr->data, ptr->next->data) > 0) {
                // Swap data of adjacent nodes
                void* temp_data = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp_data;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last_ptr = ptr;  // Move the boundary of unsorted part of the list
    } while (swapped);
}

int main() {
    DoublyLinkedList* list = create_list();
    int *a = (int*)malloc(sizeof(int)), *b = (int*)malloc(sizeof(int)), *c = (int*)malloc(sizeof(int));
    *a = 30; *b = 20; *c = 10;

    insert_front(list, a, sizeof(int));
    insert_front(list, b, sizeof(int));
    insert_back(list, c, sizeof(int));

    printf("List forward before sorting: ");
    traverse_forward(list, print_int);
    printf("\n");

    // Sort the list
    bubble_sort(list, compare_int);

    printf("List forward after sorting: ");
    traverse_forward(list, print_int);
    printf("\n");

    int target = 10;
    Node* found = search(list, &target, compare_int);
    if (found) printf("Found: %d\n", *(int*)found->data);

    delete_node(list, &target, compare_int);
    printf("After deletion forward: ");
    traverse_forward(list, print_int);
    printf("\n");

    int* front = (int*)delete_front(list);  // Cast to int*
    if (front) {
        printf("Deleted front: %d\n", *front);
        free(front);  // Free the data after deletion
    }

    printf("After front deletion forward: ");
    traverse_forward(list, print_int);
    printf("\n");

    free(b);  // Ensure to free the remaining dynamically allocated memory.
    free(c);

    return 0;
}
