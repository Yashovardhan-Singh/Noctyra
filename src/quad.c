#include "include/quad.h"

#include <stdlib.h>
#include <string.h>

#define Q2D_INITIAL_CAPACITY 1024

void Q2dBufInit(Quad2dBuffer* qb) {
    qb->size = 0;
    qb->capacity = Q2D_INITIAL_CAPACITY;
    qb->data = malloc(qb->capacity * sizeof(Quad2d));
    qb->indices = malloc(qb->capacity * 6 * sizeof(u32));;
    qb->indicesCapacity = Q2D_INITIAL_CAPACITY * 6;
}

void Q2dBufFree(Quad2dBuffer* qb) {
    free(qb->data);
    qb->data = NULL;
    qb->size = 0;
    qb->capacity = 0;
}

void Q2dBufPush(Quad2dBuffer* qb, Quad2d q) {
    if (qb->size >= qb->capacity) {     // Grow the buffer capacity
        qb->capacity *= 2;      // Avoid frequent Reallocs
        qb->data = (Quad2d*) realloc(qb->data, qb->capacity * sizeof(Quad2d));
    }

    if (qb->size * 6 >= qb->indicesCapacity) {      // Grow the indices buffer
        qb->indicesCapacity *= 2;
        qb->indices = realloc(qb->indices, qb->indicesCapacity * sizeof(u32));
    }

    qb->data[qb->size] = q;

    u32 offset = qb->size * 4;

    qb->indices[qb->size * 6 + 0] = offset + 0;
    qb->indices[qb->size * 6 + 1] = offset + 1;
    qb->indices[qb->size * 6 + 2] = offset + 2;
    qb->indices[qb->size * 6 + 3] = offset + 2;
    qb->indices[qb->size * 6 + 4] = offset + 3;
    qb->indices[qb->size * 6 + 5] = offset + 1;

    qb->size++;
}

void Q2dBufPop(Quad2dBuffer* qb) {
    if (qb->size > 0) {
        qb->size--;
    }
}

void Q2dBufRemoveAt(Quad2dBuffer* qb, usize index) {
    if (index >= qb->size) return;
    memmove(&qb->data[index], &qb->data[index + 1], (qb->size - index - 1) * sizeof(Quad2d));
    qb->size--;
}

void Q2dBufClear(Quad2dBuffer* qb) {
    qb->size = 0;
}

Quad2d* Q2dBufData(Quad2dBuffer* qb) {
    return qb->data;
}

usize Q2dBufFindById(Quad2dBuffer* qb, u32 id) {
    for (usize i = 0; i < qb->size; i++) {
        if (qb->data[i].id == id) {
            return i;
        }
    }
    return (usize)-1; // Not found
}

void Q2dBufSort(Quad2dBuffer* qb, int (*cmp)(const Quad2d*, const Quad2d*)) {
    qsort(qb->data, qb->size, sizeof(Quad2d), (int(*)(const void*, const void*))cmp);
}