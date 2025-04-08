#include "include/renderer.h"

char *ReadShaderFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        E_LOG("Cannot Open Shader File", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        E_LOG("Memory Allocation Failed For Shader File");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);
    return buffer;
}

u32 CompileShader(GLenum type, const char *source) {
    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        E_LOG("Shader Compilation Failed", infoLog);
    }
    return shader;
}

Shader ShaderLoad(const char *vertexPath, const char *fragmentPath) {
    Shader shader;
    char *vertexSource = ReadShaderFile(vertexPath);
    char *fragmentSource = ReadShaderFile(fragmentPath);

    if (!vertexSource || !fragmentSource) {
        E_LOG("Failed To Load Shader Files");
        shader.ProgramID = 0;
        return shader;
    }

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    free(vertexSource);
    free(fragmentSource);

    shader.ProgramID = glCreateProgram();
    glAttachShader(shader.ProgramID, vertexShader);
    glAttachShader(shader.ProgramID, fragmentShader);
    glLinkProgram(shader.ProgramID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

// Renderer Initialization
void InitRenderer(Renderer *renderer, const char *vertexPath, const char *fragmentPath) {
    renderer->shaderCount = 1;
    renderer->shaders = (Shader *)malloc(sizeof(Shader));
    renderer->shaders[0] = ShaderLoad(vertexPath, fragmentPath);

    // Generate VAO, VBO, EBO
    glGenVertexArrays(1, &renderer->VAO);
    glGenBuffers(1, &renderer->VBO);
    glGenBuffers(1, &renderer->EBO);

    // printf("VAO: %u, VBO: %u, EBO: %u\n", renderer->VAO, renderer->VBO, renderer->EBO);

    glBindVertexArray(renderer->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AddShader(Renderer *renderer, const char *vertexPath, const char *fragmentPath) {
    renderer->shaderCount++;
    renderer->shaders = (Shader *)realloc(renderer->shaders, renderer->shaderCount * sizeof(Shader));
    renderer->shaders[renderer->shaderCount - 1] = ShaderLoad(vertexPath, fragmentPath);
}

void UseShader(Renderer *renderer, u32 index) {
    if (index >= 0 && index < renderer->shaderCount) {
        glUseProgram(renderer->shaders[index].ProgramID);
    } else {
        E_LOG("Invalid Shader Index", index);
    }
}

void UploadData(Renderer *renderer, const Quad2dBuffer* qb) {
    glBindVertexArray(renderer->VAO);

    Vertex vertices[qb->size * 4];

    for (int i = 0; i < qb->size; i++) {
        vertices[i * 4 + 0] = qb->data[i].a;
        vertices[i * 4 + 1] = qb->data[i].b;
        vertices[i * 4 + 2] = qb->data[i].c;
        vertices[i * 4 + 3] = qb->data[i].d;
    }

    // Upload Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Upload Index Data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, qb->size * 6 * sizeof(unsigned int), qb->indices, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
}

// Render Function
void Draw(Renderer *renderer, u32 shaderIndex, u32 numElements, u32 textureId) {
    glBindVertexArray(renderer->VAO);
    glBindTexture(GL_TEXTURE_2D, textureId);
    UseShader(renderer, shaderIndex);
    glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Cleanup Function
void DestroyRenderer(Renderer *renderer) {
    for (u32 i = 0; i < renderer->shaderCount; i++) {
        glDeleteProgram(renderer->shaders[i].ProgramID);
    }
    free(renderer->shaders);
    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glDeleteBuffers(1, &renderer->EBO);
}

void SetBackgroundColor(Color col) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(col.r, col.g, col.b, col.a);
}