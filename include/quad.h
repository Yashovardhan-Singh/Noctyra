#ifndef SHAPES_H
#define SHAPES_H

#include "utils.h"

typedef struct {
    f32 x, y;
    f32 u, v;
} Vertex;

typedef enum {
    LAYER_BACKGROUND,
    LAYER_FOREGROUND,
    LAYER_SPRITE_1,
    LAYER_SPRITE_2,
    LAYER_PLAYER,
    LAYER_UI
} Layer;

/*
Vertex layout:
A ------ B
  |    |
  |    |
C ------ D
*/
typedef struct {
    u32 id;
    Layer layer;
    Vertex a, b, c, d;
} Quad2d;

typedef struct {
    Quad2d* data;
    usize size;
    usize capacity;
    u32 *indices;
    usize indicesCapacity;
} Quad2dBuffer;

void Q2dBufInit(Quad2dBuffer* qb);
void Q2dBufFree(Quad2dBuffer* qb);

void Q2dBufPush(Quad2dBuffer* qb, Quad2d q);
void Q2dBufPop(Quad2dBuffer* qb);
void Q2dBufRemoveAt(Quad2dBuffer* qb, usize index);

void Q2dBufClear(Quad2dBuffer *qb);

Quad2d* Q2dBufData();

usize Q2dBufFindById(Quad2dBuffer *qb, u32 id);
void Q2dBufSort(Quad2dBuffer *qb, int (*cmp)(const Quad2d*, const Quad2d*));

#endif