#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void* data;           // Raw memory block
    size_t size;          // Number of elements currently stored
    size_t capacity;      // Total allocated slots
    size_t elementSize;   // Size of each element (e.g., sizeof(int))
} RawArray;

RawArray* createArray(size_t initialCapacity, size_t elementSize) {
    RawArray* arr = malloc(sizeof(RawArray));
    arr->data = malloc(initialCapacity * elementSize);
    arr->size = 0;
    arr->capacity = initialCapacity;
    arr->elementSize = elementSize;
    return arr;
}

void resizeArray(RawArray* arr) {
    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->capacity * arr->elementSize);
    printf("Resized array to capacity: %zu\n", arr->capacity);
}

void pushInt(RawArray* arr, int value) {
    if (arr->size >= arr->capacity) {
        resizeArray(arr);
    }
    void* target = (char*)arr->data + arr->size * arr->elementSize;
    *(int*)target = value;
    arr->size++;
}

void setInt(RawArray* arr, size_t index, int value) {
    if (index >= arr->size) {
        printf("Index out of bounds!\n");
        return;
    }
    void* target = (char*)arr->data + index * arr->elementSize;
    *(int*)target = value;
}

int getInt(RawArray* arr, size_t index) {
    if (index >= arr->size) {
        printf("Index out of bounds!\n");
        return -1;
    }
    void* target = (char*)arr->data + index * arr->elementSize;
    return *(int*)target;
}

void removeAt(RawArray* arr, size_t index) {
    if (index >= arr->size) {
        printf("Index out of bounds!\n");
        return;
    }
    void* target = (char*)arr->data + index * arr->elementSize;
    void* next = (char*)target + arr->elementSize;
    size_t bytesToMove = (arr->size - index - 1) * arr->elementSize;
    memmove(target, next, bytesToMove);
    arr->size--;
}

void printIntArray(RawArray* arr) {
    printf("Array elements: ");
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", getInt(arr, i));
    }
    printf("\n");
}

void destroyArray(RawArray* arr) {
    free(arr->data);
    free(arr);
}


int main() {
    RawArray* arr = createArray(2, sizeof(int)); // start small for demo

    pushInt(arr, 10);
    pushInt(arr, 20);
    pushInt(arr, 30); // triggers resize
    pushInt(arr, 40);

    printIntArray(arr);

    printf("Removing element at index 1...\n");
    removeAt(arr, 1);

    printIntArray(arr);

    destroyArray(arr);
    return 0;
}
