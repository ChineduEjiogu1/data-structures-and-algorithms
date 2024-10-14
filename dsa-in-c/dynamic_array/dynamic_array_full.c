#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *array;
    int size;
    int max_size;
} SortedArray;

SortedArray* create_sorted_array(int max_size) {
    SortedArray *sa = (SortedArray *)malloc(sizeof(SortedArray));
    sa->array = (int *)malloc(max_size * sizeof(int));
    sa->size = 0;
    sa->max_size = max_size;
    return sa;
}

int get_size(SortedArray *sa) {
    return sa->size;
}

int get_element(SortedArray *sa, int index) {
    if (index < 0 || index >= sa->size) {
        printf("Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return sa->array[index];
}

void insert_element(SortedArray *sa, int value) {
    if (sa->size >= sa->max_size) {
        printf("The array is already full\n");
        exit(EXIT_FAILURE);
    }
    int i = sa->size - 1;
    while (i >= 0 && sa->array[i] > value) {
        sa->array[i + 1] = sa->array[i];
        i--;
    }
    sa->array[i + 1] = value;
    sa->size++;
}

int linear_search(SortedArray *sa, int target) {
    for (int i = 0; i < sa->size; i++) {
        if (sa->array[i] == target) {
            return i;
        } else if (sa->array[i] > target) {
            break;
        }
    }
    return -1;
}

int binary_search(SortedArray *sa, int target) {
    int left = 0;
    int right = sa->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sa->array[mid] == target) {
            return mid;
        } else if (sa->array[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

void delete_element(SortedArray *sa, int target) {
    int index = binary_search(sa, target);
    if (index == -1) {
        printf("Unable to delete element %d: the entry is not in the array\n", target);
        return;
    }
    for (int i = index; i < sa->size - 1; i++) {
        sa->array[i] = sa->array[i + 1];
    }
    sa->size--;
}

void free_sorted_array(SortedArray *sa) {
    free(sa->array);
    free(sa);
}

int main() {
    SortedArray *sa = create_sorted_array(5);
    insert_element(sa, 10);
    insert_element(sa, 20);
    insert_element(sa, 30);
    delete_element(sa, 20);

    for (int i = 0; i < sa->size; i++) {
        printf("%d ", sa->array[i]);
    }
    printf("\n");

    free_sorted_array(sa);

    return 0;
}
