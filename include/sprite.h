#ifndef SPRITE_H
#define SPRITE_H

#include "window.h"
#include "color.h"
#include "vec.h"
#include "quad.h"
#include "utils.h"

typedef struct {
    Vec2 pos;       // ScreenSpace
    Vec2 size;      // ScreenSpace
    Vec2 uv_min;    // ScreenSpace
    Layer layer;
    u32 id;
} Sprite;

void PushSprite(Sprite s, Vec2 screenSize, Quad2dBuffer* qb);

#endif