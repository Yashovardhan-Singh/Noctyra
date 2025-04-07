#ifndef VEC_H
#define VEC_H

#include "utils.h"
#include <math.h>

typedef struct {
    float x, y;
} Vec2;

Vec2 Vec2Add(Vec2 a, Vec2 b);
Vec2 Vec2Sub(Vec2 a, Vec2 b);
Vec2 Vec2Negate(Vec2 v);
Vec2 Vec2Scale(Vec2 v, f32 scale);
Vec2 Vec2DivScalar(Vec2 v, f32 dividend); // If dividend is 0, then returns input Vector v
f32 Vec2Len(Vec2 v); // Rename this to magnitude?
Vec2 Vec2Normalize(Vec2 v);
f32 Vec2Dot(Vec2 a, Vec2 b);
Vec2 Vec2Perpendicular(Vec2 v);
f32 Vec2Distance(Vec2 source, Vec2 target);
Vec2 Vec2Reflect(Vec2 invector, Vec2 normal);
Vec2 Vec2Lerp(Vec2 v0, Vec2 v1, f32 t); // parameter "t" MUST BE in range [0, 1] OR IT WON'T WORK
f32 Vec2Project(Vec2 a, Vec2 b); // Projection of vector a on vector b
Vec2 Vec2Rotate(Vec2 v, Vec2 p, f32 degrees); // rotate v, around point p, degrees is degrees

#endif