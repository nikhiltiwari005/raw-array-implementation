#include <stdio.h>

// Forward declare functions from generic_array.c
RawArray* createArray(size_t, size_t);
void push(RawArray*, void*);
void get(RawArray*, size_t, void*);
void set(RawArray*, size_t, void*);
void removeAt(RawArray*, size_t);
void destroyArray(RawArray*);
#define PUSH(arr, val) do { typeof(val) _tmp = (val); push((arr), &_tmp); } while(0)
#define GET(arr, idx, outVar) get((arr), (idx), &(outVar))
#define SET(arr, idx, val) do { typeof(val) _tmp = (val); set((arr), (idx), &_tmp); } while(0)

int main() {
    // 🧪 Test with int
    RawArray* intArray = createArray(2, sizeof(int));
    PUSH(intArray, 10);
    PUSH(intArray, 20);
    PUSH(intArray, 30);

    int val;
    for (size_t i = 0; i < intArray->size; i++) {
        GET(intArray, i, val);
        printf("intArray[%zu] = %d\n", i, val);
    }

    // 🧪 Test with float
    RawArray* floatArray = createArray(2, sizeof(float));
    PUSH(floatArray, 1.5f);
    PUSH(floatArray, 2.5f);
    PUSH(floatArray, 3.5f);

    float fval;
    for (size_t i = 0; i < floatArray->size; i++) {
        GET(floatArray, i, fval);
        printf("floatArray[%zu] = %.2f\n", i, fval);
    }

    // 🧪 Remove and test again
    printf("Removing intArray[1]...\n");
    removeAt(intArray, 1);
    for (size_t i = 0; i < intArray->size; i++) {
        GET(intArray, i, val);
        printf("intArray[%zu] = %d\n", i, val);
    }

    destroyArray(intArray);
    destroyArray(floatArray);
    return 0;
}
