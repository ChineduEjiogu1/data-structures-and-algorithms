#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the stack is empty
int isEmpty(struct Node* top) {
    return top == NULL;
}

// Push function to add data to the stack
void push(struct Node** top, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
    printf("Pushed %d onto the stack\n", data);
}

// Pop function to remove and return the top element
int pop(struct Node** top) {
    if (isEmpty(*top)) {
        printf("Stack underflow\n");
        exit(1);
    }
    struct Node* temp = *top;
    *top = (*top)->next;
    int poppedData = temp->data;
    free(temp);
    return poppedData;
}

// Peek function to get the top element of the stack without removing it
int peek(struct Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return top->data;
}

// Function to display the stack
void display(struct Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty\n");
        return;
    }
    struct Node* temp = top;
    printf("Stack elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to demonstrate stack operations
int main() {
    struct Node* stack = NULL;

    // Perform stack operations
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    
    display(stack);
    
    printf("Top element is %d\n", peek(stack));

    printf("Popped element is %d\n", pop(&stack));
    display(stack);

    return 0;
}
