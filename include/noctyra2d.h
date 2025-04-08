/*
Noctyra2D — 2D Game Engine  
Copyright (C) 2025 Yashovardhan Singh  
All Rights Reserved Except Where Otherwise Stated.

Licensed Under The GNU Affero General Public License v3.0 (AGPL-3.0)  
See LICENSE And LICENSE-EXCEPTIONS For Details.

Additional Conditions Apply:  
- Attribution Required  
- No DRM  
- No Military Use  
- Trademark Protection Applies To The Name "Noctyra2D"

This Software Is Provided "As-Is" Without Warranty Of Any Kind.

Contributions Are Copyright Their Respective Authors  
And Licensed Under AGPL-3.0 Unless Stated Otherwise.

Powered By Noctyra2D — (c) 2025 Yashovardhan Singh
*/

#ifndef NOCTYRA2D_H
#define NOCTYRA2d_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STATIC_INLINE inline static __attribute__((always_inline)) 

// Color
typedef struct {
    float r, g, b, a;
} Color;

// Grayscale
#define COLOR_WHITE      ((Color){1.0f, 1.0f, 1.0f, 1.0f})
#define COLOR_BLACK      ((Color){0.0f, 0.0f, 0.0f, 1.0f})
#define COLOR_GRAY       ((Color){0.5f, 0.5f, 0.5f, 1.0f})

// Primary Colors
#define COLOR_RED        ((Color){1.0f, 0.0f, 0.0f, 1.0f})
#define COLOR_GREEN      ((Color){0.0f, 1.0f, 0.0f, 1.0f})
#define COLOR_BLUE       ((Color){0.0f, 0.0f, 1.0f, 1.0f})

// Secondary Colors
#define COLOR_YELLOW     ((Color){1.0f, 1.0f, 0.0f, 1.0f})
#define COLOR_CYAN       ((Color){0.0f, 1.0f, 1.0f, 1.0f})
#define COLOR_MAGENTA    ((Color){1.0f, 0.0f, 1.0f, 1.0f})

// Extras
#define COLOR_ORANGE     ((Color){1.0f, 0.5f, 0.0f, 1.0f})
#define COLOR_PURPLE     ((Color){0.5f, 0.0f, 0.5f, 1.0f})
#define COLOR_TRANSPARENT ((Color){0.0f, 0.0f, 0.0f, 0.0f})





// utils
// Unsigned Integer Types
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// Signed Integer Types
typedef signed char      i8;
typedef signed short     i16;
typedef signed int       i32;
typedef signed long long i64;

// Floating Point Types
typedef float  f32;
typedef double f64;

typedef void* ptr;
typedef char* str;

typedef u8 bool;

#define true  1
#define false 0

#if defined(__x86_64__) || defined(__aarch64__) || defined(_M_x64)
    typedef u64 usize;
#else
    typedef u32 usize;
#endif

// Platform-Specific Type Definitions
#if defined(_WIN32) || defined(_WIN64)
    typedef unsigned long ulong;
    typedef signed long slong;
#elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
    typedef unsigned long ulong;
    typedef signed long slong;
#endif

// Generic logging macro
#define LOG(level, msg, ...) fprintf(stdout, "[%s] %s:%d: " msg "\n", level, __FILE__, __LINE__, ##__VA_ARGS__)

// Specific case defines
#define E_LOG(msg, ...) LOG("ERROR", msg, ##__VA_ARGS__)    // error
#define W_LOG(msg, ...) LOG("WARN", msg, ##__VA_ARGS__)     // warn
#define I_LOG(msg, ...) LOG("INFO", msg, ##__VA_ARGS__)     // info

STATIC_INLINE f32 PixelToNdcX(f32 x, f32 screenWidth) {
    return (x / screenWidth) * 2.0f - 1.0f;
}

STATIC_INLINE f32 PixelToNdcY(f32 y, f32 screenHeight) {
    return (y / screenHeight) * 2.0f - 1.0f;
}





// Quad
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





// vec
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





// window
typedef struct {
    GLFWwindow *handle;
    int width, height;
    const char *title;
} Window;

void InitWindow(Window* win, int width, int height, const char* title);
void UpdateWindow(Window* win);
void DestroyWindow(Window* win);
int WindowShouldClose(Window* win);
Vec2 ScreenSize(Window *win);





// renderer
typedef struct {
    u32 ProgramID;
} Shader;

typedef struct {
    u32 VAO, VBO, EBO;
    Shader* shaders;
    i32 shaderCount;
} Renderer;

Shader ShaderLoad(const char *vertexPath, const char *fragmentPath);
void InitRenderer(Renderer *renderer, const char *vertexPath, const char *fragmentPath);
void AddShader(Renderer *renderer, const char *vertexPath, const char *fragmentPath);
void UseShader(Renderer *renderer, u32 index);
void UploadData(Renderer *renderer, const Quad2dBuffer *qb);
void Draw(Renderer *renderer, u32 shaderIndex, u32 numIndices, u32 textureId);
void DestroyRenderer(Renderer *renderer);
void SetBackgroundColor(Color col);





// sprite
typedef struct {
    Vec2 pos;       // ScreenSpace
    Vec2 size;      // ScreenSpace
    Vec2 uv_min;    // ScreenSpace
    Layer layer;
    u32 id;
} Sprite;

void PushSprite(Sprite s, Vec2 screenSize, Quad2dBuffer* qb);





// texture
typedef struct {
    u32 id;
    Vec2 size;
} Texture;

Texture LoadTexture(const char* path);
void FreeTexture(Texture* tex);


#endif