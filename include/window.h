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

#ifndef WINDOW_H
#define WINDOW_H

#include "vendor/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "include/utils.h"

typedef struct {
    GLFWwindow *handle;
    int width, height;
    const char *title;
} Window;

void InitWindow(Window* win, int width, int height, const char* title);
void UpdateWindow(Window* win);
void DestroyWindow(Window* win);
int WindowShouldClose(Window* win);

#endif