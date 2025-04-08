#include "include/window.h"

// call back from fixing framebuffer on window resize
void _FrameBufferSizeCallback(GLFWwindow* win, int width, int height) {
    glViewport(0, 0, width, height);
}

void InitWindow(Window* win, int width, int height, const char* title) {
    if (!glfwInit()) {
        E_LOG("Failure initializing GLFW");
        glfwTerminate();
        return;
    }

    // version 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!win->handle) {
        E_LOG("Failure creating window");
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(win->handle);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        E_LOG("Failure initializing");
        glfwTerminate();
        return;
    }

    win->width = width;
    win->height = height;

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(win->handle, _FrameBufferSizeCallback);
}

void UpdateWindow(Window* win) {
    glfwSwapBuffers(win->handle);
    glfwPollEvents();
}

void DestroyWindow(Window *win) {
    glfwDestroyWindow(win->handle);
    glfwTerminate();
}

int WindowShouldClose(Window *win) {
    return glfwWindowShouldClose(win->handle);
}

Vec2 ScreenSize(Window* win) {
    return (Vec2) { win->width, win->height};
}