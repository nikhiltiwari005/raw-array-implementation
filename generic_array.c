#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ✅ Core Dynamic Array Definition
typedef struct {
    void* data;
    size_t size;
    size_t capacity;
    size_t elementSize;
} RawArray;

// ✅ Create a new array
RawArray* createArray(size_t initialCapacity, size_t elementSize) {
    RawArray* arr = malloc(sizeof(RawArray));
    arr->data = malloc(initialCapacity * elementSize);
    arr->size = 0;
    arr->capacity = initialCapacity;
    arr->elementSize = elementSize;
    return arr;
}

// ✅ Resize the array when full
void resizeArray(RawArray* arr) {
    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->capacity * arr->elementSize);
    printf("Resized to capacity: %zu\n", arr->capacity);
}

// ✅ Generic push
void push(RawArray* arr, void* element) {
    if (arr->size >= arr->capacity) {
        resizeArray(arr);
    }
    void* target = (char*)arr->data + arr->size * arr->elementSize;
    memcpy(target, element, arr->elementSize);
    arr->size++;
}

// ✅ Generic get
void get(RawArray* arr, size_t index, void* out) {
    if (index >= arr->size) {
        printf("Index out of bounds!\n");
        return;
    }
    void* source = (char*)arr->data + index * arr->elementSize;
    memcpy(out, source, arr->elementSize);
}

// ✅ Generic set
void set(RawArray* arr, size_t index, void* element) {
    if (index >= arr->size) {
        printf("Index out of bounds!\n");
        return;
    }
    void* target = (char*)arr->data + index * arr->elementSize;
    memcpy(target, element, arr->elementSize);
}

// ✅ Remove by index
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

// ✅ Destroy array
void destroyArray(RawArray* arr) {
    free(arr->data);
    free(arr);
}

// ✅ Type-safe macro wrappers
#define PUSH(arr, val) do { typeof(val) _tmp = (val); push((arr), &_tmp); } while(0)
#define GET(arr, idx, outVar) get((arr), (idx), &(outVar))
#define SET(arr, idx, val) do { typeof(val) _tmp = (val); set((arr), (idx), &_tmp); } while(0)
