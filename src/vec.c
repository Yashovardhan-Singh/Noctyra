#include "include/vec.h"

#include "vendor/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

Vec2 Vec2Add(Vec2 a, Vec2 b) {
    return (Vec2) { a.x + b.x, a.y + b.y };
}

Vec2 Vec2Sub(Vec2 a, Vec2 b) {
    return (Vec2) { a.x - b.x, a.y - b.y };
}

Vec2 Vec2Negate(Vec2 v) {
    return (Vec2) { -v.x , -v.y };
}

Vec2 Vec2Scale(Vec2 v, f32 scale) {
    return (Vec2) { v.x * scale, v.y * scale };
}

// If dividend is 0, then returns input Vector v
Vec2 Vec2DivScalar(Vec2 v, f32 dividend) {
    if (dividend != 0) // division by zero guard
        return (Vec2) { v.x / dividend, v.y  / dividend };
    else return v;
}

// Rename this to magnitude?
f32 Vec2Len(Vec2 v) {
    return sqrtf(v.x*v.x + v.y*v.y);
}

Vec2 Vec2Normalize(Vec2 v) {
    f32 len = Vec2Len(v);
    return (Vec2) { v.x / len, v.y / len };
}

f32 Vec2Dot(Vec2 a, Vec2 b) {
    return (a.x * b.x) + (a.y * b.y);
}

Vec2 Vec2Perpendicular(Vec2 v) {
    return (Vec2) { -v.y, v.x };
}

f32 Vec2Distance(Vec2 source, Vec2 target) {
    return sqrtf(
        (target.x - source.x) * (target.x - source.x) +
        (target.y - source.y) * (target.y - source.y)
    );
}

// Reflect invector across Vec2 normal
// Vec2 parameter "Normal", is normalized inside the function
Vec2 Vec2Reflect(Vec2 invector, Vec2 normal) {
    Vec2 n = Vec2Normalize(normal);     // normalised
    f32 dotted = Vec2Dot(invector, n);  // invector . normalized(normal)
    Vec2 v_subtrahend = Vec2Scale(n, dotted * 2);   // normal scaled by 2*(invector . normalized(normal))
    return Vec2Sub(invector, v_subtrahend);     // invector - scaled(normal)
}

// parameter "t" MUST BE in range [0, 1] OR IT WON'T WORK
Vec2 Vec2Lerp(Vec2 v0, Vec2 v1, f32 t) {
    Vec2 param1 = Vec2Scale(v0, (1.0f - t));
    Vec2 param2 = Vec2Scale(v1, t);
    return Vec2Add(param1, param2);
}

// Projection of vector a on vector b
f32 Vec2Project(Vec2 a, Vec2 b) {
    return Vec2Dot(a, b) / Vec2Len(b);
}

// rotate v, around point p, degrees is degrees
Vec2 Vec2Rotate(Vec2 v, Vec2 p, f32 degrees) {
    Vec2 opvec = Vec2Sub(v, p);
    f32 costheta = cosf32(degrees);
    f32 sintheta = sinf32(degrees);
    f32 new_x = (opvec.x * costheta) - (opvec.y * sintheta);
    f32 new_y = (opvec.y * costheta) + (opvec.x * sintheta);
    return Vec2Add((Vec2) { new_x, new_y }, p);
}