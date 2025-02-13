#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 50000 // Hash table size

// Optimized djb2 hash function
unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % CAPACITY;
}

// Defines the HashTable item.
typedef struct Ht_item {
    char *key;
    char *value;
} Ht_item;

// Defines the LinkedList for collision resolution.
typedef struct LinkedList {
    Ht_item *item;
    struct LinkedList *next;
} LinkedList;

// Defines the HashTable.
typedef struct HashTable {
    Ht_item **items;
    LinkedList **overflow_buckets;
    int size;
    int count;
} HashTable;

// Allocates memory for a LinkedList node.
LinkedList *allocate_list(Ht_item *item) {
    LinkedList *node = (LinkedList *)malloc(sizeof(LinkedList));
    node->item = item;
    node->next = NULL;
    return node;
}

// Inserts an item into a LinkedList.
void linkedlist_insert(LinkedList **list, Ht_item *item) {
    LinkedList *node = allocate_list(item);
    node->next = *list; // Insert at head
    *list = node;
}

// Removes an item from a LinkedList and returns it.
Ht_item *linkedlist_remove(LinkedList **list, const char *key) {
    LinkedList *curr = *list, *prev = NULL;
    while (curr) {
        if (strcmp(curr->item->key, key) == 0) {
            Ht_item *item = curr->item;
            if (prev)
                prev->next = curr->next;
            else
                *list = curr->next;
            free(curr);
            return item;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

// Frees a LinkedList.
void free_linkedlist(LinkedList *list) {
    while (list) {
        LinkedList *temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

// Creates overflow buckets (array of LinkedLists).
LinkedList **create_overflow_buckets(int size) {
    return (LinkedList **)calloc(size, sizeof(LinkedList *));
}

// Frees all overflow bucket lists.
void free_overflow_buckets(HashTable *table) {
    for (int i = 0; i < table->size; i++)
        free_linkedlist(table->overflow_buckets[i]);
    free(table->overflow_buckets);
}

// Creates a new key-value item.
Ht_item *create_item(const char *key, const char *value) {
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

// Creates a new HashTable.
HashTable *create_table(int size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)calloc(size, sizeof(Ht_item *));
    table->overflow_buckets = create_overflow_buckets(size);
    return table;
}

// Frees an item.
void free_item(Ht_item *item) {
    free(item->key);
    free(item->value);
    free(item);
}

// Frees the entire HashTable.
void free_table(HashTable *table) {
    for (int i = 0; i < table->size; i++)
        if (table->items[i])
            free_item(table->items[i]);
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

// Handles collisions by inserting into the linked list.
void handle_collision(HashTable *table, int index, Ht_item *item) {
    linkedlist_insert(&table->overflow_buckets[index], item);
}

// Inserts a key-value pair into the HashTable.
void ht_insert(HashTable *table, const char *key, const char *value) {
    if (table->count >= table->size) {
        printf("Insert Error: Hash Table is full\n");
        return;
    }

    int index = hash_function(key);
    Ht_item *existing = table->items[index];

    if (!existing) {
        table->items[index] = create_item(key, value);
    } else if (strcmp(existing->key, key) == 0) {
        // Update existing key
        free(existing->value);
        existing->value = strdup(value);
    } else {
        // Handle collision
        handle_collision(table, index, create_item(key, value));
    }

    table->count++;
}

// Searches for a key in the HashTable.
char *ht_search(HashTable *table, const char *key) {
    int index = hash_function(key);
    Ht_item *item = table->items[index];

    if (item && strcmp(item->key, key) == 0)
        return item->value;

    // Search collision list
    LinkedList *head = table->overflow_buckets[index];
    while (head) {
        if (strcmp(head->item->key, key) == 0)
            return head->item->value;
        head = head->next;
    }

    return NULL;
}

// Deletes a key from the HashTable.
void ht_delete(HashTable *table, const char *key) {
    int index = hash_function(key);
    Ht_item *item = table->items[index];

    if (!item) return; // Key not found

    if (strcmp(item->key, key) == 0) {
        free_item(item);
        table->items[index] = NULL;
        table->count--;
    } else {
        // Remove from collision list
        Ht_item *removed = linkedlist_remove(&table->overflow_buckets[index], key);
        if (removed) {
            free_item(removed);
            table->count--;
        }
    }
}

// Prints the search result.
void print_search(HashTable *table, const char *key) {
    char *val = ht_search(table, key);
    if (val)
        printf("Key:%s, Value:%s\n", key, val);
    else
        printf("Key:%s does not exist\n", key);
}

// Prints the HashTable.
void print_table(HashTable *table) {
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (table->items[i])
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);
    }
    printf("-------------------\n\n");
}

// Main function
int main() {
    HashTable *ht = create_table(CAPACITY);
    ht_insert(ht, "1", "First address");
    ht_insert(ht, "2", "Second address");
    ht_insert(ht, "Hel", "Third address");
    ht_insert(ht, "Cau", "Fourth address");

    print_search(ht, "1");
    print_search(ht, "2");
    print_search(ht, "3");
    print_search(ht, "Hel");
    print_search(ht, "Cau");

    print_table(ht);

    ht_delete(ht, "1");
    ht_delete(ht, "Cau");

    print_table(ht);
    free_table(ht);
    return 0;
}
