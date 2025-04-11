#include "include/texture.h"

#include "vendor/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/include/stb_image.h"

Texture LoadTexture(const char* path) {
    int w, h, ch;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(path, &w, &h, &ch, 0);
    if (!data) {
        E_LOG("Can't load texture data");
        return (Texture) {0};
    }

    u32 tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, ch == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return (Texture) {
        .id = tex,
        .size = (Vec2) { (float)w, (float)h }
    };
}

void FreeTexture(Texture* tex) {
    if (tex->id) {
        glDeleteTextures(1, &tex->id);
        tex->id = 0;
    }
}