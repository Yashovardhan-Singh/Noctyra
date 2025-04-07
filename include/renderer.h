#ifndef RENDERER_H
#define RENDERER_H

#include "vendor/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/quad.h"
#include "include/utils.h"
#include "include/color.h"

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
void Draw(Renderer *renderer, u32 shaderIndex, u32 numIndices);
void DestroyRenderer(Renderer *renderer);
void SetBackgroundColor(Color col);

#endif