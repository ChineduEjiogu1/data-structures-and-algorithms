#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct HashNode
{
    char *key;
    int value;
    struct HashNode *next; // For handling collisions using chaining
} HashNode;

typedef struct HashTable
{
    HashNode *buckets[TABLE_SIZE];
} HashTable;

// Hash function
unsigned int hash(const char *key)
{
    unsigned int hash = 0;
    while (*key)
    {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}

// Create a new hash node
HashNode *create_node(const char *key, int value)
{
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Initialize the hash table
HashTable *create_table()
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table->buckets[i] = NULL;
    }
    return table;
}

// Insert a key-value pair into the hash table
void insert(HashTable *table, const char *key, int value)
{
    unsigned int index = hash(key) % TABLE_SIZE;  // Ensure valid index
    HashNode *new_node = create_node(key, value);

    if (!new_node) {
        printf("Memory allocation failed for new node\n");
        return;
    }

    // Collision handling using chaining
    HashNode *current = table->buckets[index];
    HashNode *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;  // Update value
            free(new_node->key);
            free(new_node);  // Avoid memory leak
            return;
        }
        prev = current;
        current = current->next;
    }

    // If key doesn't exist, insert at the beginning of the list
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

// Search for a value by key
int search(HashTable *table, const char *key)
{
    unsigned int index = hash(key);
    HashNode *current = table->buckets[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Key not found
}

// Delete a key-value pair from the hash table
void delete(HashTable *table, const char *key)
{
    unsigned int index = hash(key);
    HashNode *current = table->buckets[index];
    HashNode *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                table->buckets[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Free the hash table
void free_table(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *current = table->buckets[i];
        while (current != NULL)
        {
            HashNode *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table);
}

// Main function to demonstrate usage
int main()
{
    HashTable *table = create_table();

    insert(table, "apple", 10);
    insert(table, "banana", 20);
    insert(table, "orange", 30);

    printf("Value for 'apple': %d\n", search(table, "apple"));
    printf("Value for 'banana': %d\n", search(table, "banana"));
    printf("Value for 'grape': %d\n", search(table, "grape"));

    delete (table, "banana");
    printf("Value for 'banana' after deletion: %d\n", search(table, "banana"));

    free_table(table);
    return 0;
}