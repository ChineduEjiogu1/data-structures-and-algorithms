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
    free(to_delete);
    return data;
}

void print_int(void* data) {
    printf("%d ", *(int*)data);
}

int compare_int(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

int main() {
    DoublyLinkedList* list = create_list();
    int a = 10, b = 20, c = 30;

    insert_front(list, &a, sizeof(int));
    insert_front(list, &b, sizeof(int));
    insert_back(list, &c, sizeof(int));

    printf("List forward: ");
    traverse_forward(list, print_int);
    printf("\n");

    printf("List backward: ");
    traverse_backward(list, print_int);
    printf("\n");

    int target = 10;
    Node* found = search(list, &target, compare_int);
    if (found) printf("Found: %d\n", *(int*)found->data);

    delete_node(list, &target, compare_int);
    printf("After deletion forward: ");
    traverse_forward(list, print_int);
    printf("\n");

    int* front = (int*)delete_front(list);

    if (front) {
        printf("Deleted front: %d\n", *front);
        free(front);
    }

    printf("After front deletion forward: ");
    traverse_forward(list, print_int);
    printf("\n");

    return 0;
}