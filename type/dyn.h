#ifndef DYN_H
#define DYN_H

#include <stdlib.h>

typedef struct {
    void* data;
    size_t size;
    size_t capac;
    size_t sizeofElem;
} dyn;

void cbDynArrInit(dyn* arr, size_t type);
void cbDynArrPushBack(dyn* arr, void* val);
void cbDynArrRemoveUnordered(dyn* arr, size_t idx);
void* cbDynArrIndex(dyn* arr, size_t idx);
void cbDynArrFree(dyn* arr);
void cbDynArrClear(dyn* arr);

#endif
