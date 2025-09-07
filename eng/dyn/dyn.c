#include "dyn.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define nil NULL

void cbDynArrInit(dyn* arr, size_t elemSize) {
    arr->data = nil;
    arr->size = 0;
    arr->capac = 0;
    arr->sizeofElem = elemSize;
}

void cbDynArrPushBack(dyn* arr, void* val) {
    if (arr->size == arr->capac) {
        size_t newCapac = arr->capac == 0? 4 : arr->capac * 2;
        void* newData = realloc(arr->data, newCapac * arr->sizeofElem);
        if (!newData) {
            printf("realloc failed!\n");
            exit(1);
        }
        arr->data = newData;
        arr->capac = newCapac;
    }
    memcpy((char*)arr->data + arr->size * arr->sizeofElem, val, arr->sizeofElem);
    arr->size++;
}

void* cbDynArrIndex(dyn* arr, size_t idx) {
    if (idx >= arr->size) {
        printf("index out of bounds! %d >= %d\n", (int)idx, (int)arr->size);
        exit(1);
    }
    return (char*)arr->data + idx * arr->sizeofElem;
}

void cbDynArrFree(dyn* arr) {
    free(arr->data);
    arr->data = nil;
    arr->size = 0;
    arr->capac = 0;
    arr->sizeofElem = 0;
}

void cbDynArrClear(dyn* arr) {
    arr->size = 0;
}
