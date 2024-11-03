#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definition of a Node in a singly linked list
struct Node {
    int data;          
    struct Node* next;
};

// Function to create a new Node
struct Node* newNode(int data) {
    struct Node* temp = 
      (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Function to traverse and print the elements 
// of the linked list
void traverseLinkedList(struct Node* head)
{
    // Start from the head of the linked list
    struct Node* current = head;

    // Traverse the linked list until reaching the end (NULL)
    while (current != NULL) {

        // Print the data of the current node
        printf("%d ", current->data);

        // Move to the next node
        current = current->next;
    }

    printf("\n");
}

// Function to search for a value in the Linked List
bool searchLinkedList(struct Node* head, int target)
{
    // Traverse the Linked List
    while (head != NULL) {

        // Check if the current node's
        // data matches the target value
        if (head->data == target) {
            return true; // Value found
        }

        // Move to the next node
        head = head->next;
    }

    return false; // Value not found
}

// Function to find the length of the linked list
int findLength(struct Node* head)
{
    // Initialize a counter for the length
    int length = 0;

    // Start from the head of the list
    struct Node* curr = head;

    // Traverse the list and increment
    // the length for each node
    while (curr != NULL) {
        length++;
        curr = curr->next;
    }

    // Return the final length of the linked list
    return length;
}

// Function to insert a new node at the beginning of the linked list
struct Node* insertAtBeginning(struct Node* head, int value)
{
    // Create a new node with the given value
    struct Node* new_node = newNode(value);

    // Set the next pointer of the new node to the current head
    new_node->next = head;

    // Move the head to point to the new node
    head = new_node;

    // Return the new head of the linked list
    return head;
}

// Function to insert a node at the end of the linked list
struct Node* insertAtEnd(struct Node* head, int value)
{
    // Create a new node with the given value
    struct Node* new_node = newNode(value);

    // If the list is empty, make the new node the head
    if (head == NULL)
        return new_node;

    // Traverse the list until the last node is reached
    struct Node* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    // Link the new node to the current last node
    curr->next = new_node;

    return head;
}


// Function to insert a node at a specified position
struct Node* insertPos(struct Node* head, int pos, int data) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return head;
    }

    // Special case for inserting at the head
    if (pos == 1) {
        struct Node* temp = newNode(data);
        temp->next = head;
        return temp;
    }

    // Traverse the list to find the node 
    // before the insertion point
    struct Node* prev = head;
    int count = 1;
    while (count < pos - 1 && prev != NULL) {
        prev = prev->next;
        count++;
    }

    // If position is greater than the number of nodes
    if (prev == NULL) {
        printf("Invalid position!\n");
        return head;
    }

    // Insert the new node at the specified position
    struct Node* temp = newNode(data);
    temp->next = prev->next;
    prev->next = temp;

    return head;
}


// Function to remove the first node of the linked list
struct Node* removeFirstNode(struct Node* head)
{
    if (head == NULL)
        return NULL;

    // Move the head pointer to the next node
    struct Node* temp = head;
    head = head->next;

    // Free the memory of the old head
    free(temp);

    return head;
}


// Function to remove the last node of the linked list
struct Node* removeLastNode(struct Node* head)
{
    if (head == NULL)
        return NULL;

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    // Find the second last node
    struct Node* second_last = head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;

    // Delete last node
    free(second_last->next);

    // Change next of second last
    second_last->next = NULL;

    return head;
}


// Function to delete a node at a specific position
struct Node* deleteAtPosition(struct Node* head, int position)
{
    // If the list is empty or the position is invalid
    if (head == NULL || position < 1) {
        return head;
    }

    // If the head needs to be deleted
    if (position == 1) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    // Traverse to the node before the position to be deleted
    struct Node* curr = head;
    for (int i = 1; i < position - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    // If the position is out of range
    if (curr == NULL || curr->next == NULL) {
        return head;
    }

    // Store the node to be deleted
    struct Node* temp = curr->next;

    // Update the links to bypass the node to be deleted
    curr->next = curr->next->next;

    // Delete the node
    free(temp);
  
    return head;
}


// Main function to demonstrate the list usage
int main() {
    struct Node* head = NULL;

    // Insert nodes at the end of the linked list
    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);
    
    printf("Linked List after inserting at end: ");
    traverseLinkedList(head);

    // Insert node at the beginning of the linked list
    head = insertAtBeginning(head, 5);
    printf("Linked List after inserting at beginning: ");
    traverseLinkedList(head);

    // Insert node at position 3
    head = insertPos(head, 3, 15);
    printf("Linked List after inserting 15 at position 3: ");
    traverseLinkedList(head);

    // Search for a value in the linked list
    int searchValue = 20;
    if (searchLinkedList(head, searchValue)) {
        printf("Value %d found in the linked list.\n", searchValue);
    } else {
        printf("Value %d not found in the linked list.\n", searchValue);
    }

    // Find the length of the linked list
    int length = findLength(head);
    printf("Length of the linked list: %d\n", length);

    // Remove the first node
    head = removeFirstNode(head);
    printf("Linked List after removing the first node: ");
    traverseLinkedList(head);

    // Remove the last node
    head = removeLastNode(head);
    printf("Linked List after removing the last node: ");
    traverseLinkedList(head);

    // Delete node at position 2
    head = deleteAtPosition(head, 2);
    printf("Linked List after deleting node at position 2: ");
    traverseLinkedList(head);

    // Free the remaining nodes
    while (head != NULL) {
        head = removeFirstNode(head);
    }
    printf("Linked List after deleting all nodes: ");
    traverseLinkedList(head);

    return 0;
}
