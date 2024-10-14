#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int max_size;
} BoundedArray;

void double_size(BoundedArray *ba) {
    ba->max_size *= 2;
    ba->array = (int *)realloc(ba->array, ba->max_size * sizeof(int));
}

void halve_size(BoundedArray *ba) {
    ba->max_size /= 2;
    ba->array = (int *)realloc(ba->array, ba->max_size * sizeof(int));
}

void insert(BoundedArray *ba, int value) {
    if (ba->size >= ba->max_size) {
        double_size(ba);
    }
    ba->array[ba->size] = value;
    ba->size += 1;
}

int find(BoundedArray *ba, int target) {
    for (int i = 0; i < ba->size; i++) {
        if (ba->array[i] == target) {
            return i;
        }
    }
    return -1; // Not found
}

void delete(BoundedArray *ba, int target) {
    int index = find(ba, target);
    if (index == -1) {
        printf("Unable to delete element %d: the entry is not in the array\n", target);
        return;
    }
    for (int i = index; i < ba->size - 1; i++) {
        ba->array[i] = ba->array[i + 1];
    }
    ba->size -= 1;
    if (ba->max_size > 1 && ba->size <= ba->max_size / 4) {
        halve_size(ba);
    }
}

int main() {
    BoundedArray ba;
    ba.size = 0;
    ba.max_size = 5;
    ba.array = (int *)malloc(ba.max_size * sizeof(int));

    insert(&ba, 10);
    insert(&ba, 20);
    insert(&ba, 30);
    delete(&ba, 20);

    for (int i = 0; i < ba.size; i++) {
        printf("%d ", ba.array[i]);
    }
    printf("\n");

    free(ba.array);

    return 0;
}
