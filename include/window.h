#ifndef WINDOW_H
#define WINDOW_H

#include "vendor/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "include/utils.h"
#include "vec.h"

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

#endif