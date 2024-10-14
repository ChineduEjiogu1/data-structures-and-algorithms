#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// SinglyLinkedList structure
typedef struct SinglyLinkedList {
    Node* head;
} SinglyLinkedList;

// Function to create a new node
Node* create_node(void* data, size_t data_size) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    return new_node;
}

// Function to create a new empty singly linked list
SinglyLinkedList* create_singly_linked_list() {
    SinglyLinkedList* list = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    list->head = NULL;
    return list;
}

// Function to get the size of the list
int size(SinglyLinkedList* list) {
    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Function to check if the list is empty
int is_empty(SinglyLinkedList* list) {
    return list->head == NULL;
}

// Function to insert a node at the front of the list
void insert_in_front(SinglyLinkedList* list, void* data, size_t data_size) {
    Node* new_node = create_node(data, data_size);
    new_node->next = list->head;
    list->head = new_node;
}

// Function to insert a node at the back of the list
void insert_to_back(SinglyLinkedList* list, void* data, size_t data_size) {
    Node* new_node = create_node(data, data_size);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to traverse the list and apply a function to each node's data
void traverse(SinglyLinkedList* list, void (*func)(void*)) {
    Node* current = list->head;
    while (current != NULL) {
        func(current->data);
        current = current->next;
    }
}

// Function to search the list for a node with matching data (simple comparison)
Node* search(SinglyLinkedList* list, void* target, int (*cmp)(void*, void*)) {
    Node* current = list->head;
    while (current != NULL) {
        if (cmp(current->data, target) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to delete a node with the given target data
void delete_node(SinglyLinkedList* list, void* target, int (*cmp)(void*, void*)) {
    Node* current = list->head;
    Node* previous = NULL;
    while (current != NULL) {
        if (cmp(current->data, target) == 0) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->data);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Function to delete the first node in the list
void* delete_from_front(SinglyLinkedList* list) {
    if (is_empty(list)) {
        printf("Error: Delete on an empty list.\n");
        return NULL;
    }
    Node* node_to_delete = list->head;
    list->head = list->head->next;
    void* data = node_to_delete->data;
    free(node_to_delete);
    return data;
}

// Example data print function
void print_int(void* data) {
    printf("%d ", *(int*)data);
}

// Example comparison function for integers
int compare_int(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

// Main function to demonstrate the list usage
int main() {
    SinglyLinkedList* list = create_singly_linked_list();

    int a = 10, b = 20, c = 30;

    insert_in_front(list, &a, sizeof(int));
    insert_in_front(list, &b, sizeof(int));
    insert_to_back(list, &c, sizeof(int));

    printf("List contents: ");
    traverse(list, print_int);  // Output: 20 10 30
    printf("\n");

    printf("List size: %d\n", size(list));  // Output: 3

    int target = 10;
    Node* found = search(list, &target, compare_int);
    if (found) {
        printf("Found: %d\n", *(int*)found->data);
    }

    delete_node(list, &target, compare_int);
    printf("List contents after deletion: ");
    traverse(list, print_int);  // Output: 20 30
    printf("\n");

    int* front_data = (int*)delete_from_front(list);
    printf("Deleted from front: %d\n", *front_data);  // Output: 20
    free(front_data);  // Remember to free the returned data

    printf("List contents after deletion from front: ");
    traverse(list, print_int);  // Output: 30
    printf("\n");

    return 0;
}