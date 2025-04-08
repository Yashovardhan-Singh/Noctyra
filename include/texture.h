#ifndef TEXTURE_H
#define TEXTURE_H

#include "vendor/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "utils.h"
#include "vec.h"

typedef struct {
    u32 id;
    Vec2 size;
} Texture;

Texture LoadTexture(const char* path);
void FreeTexture(Texture* tex);

#endif