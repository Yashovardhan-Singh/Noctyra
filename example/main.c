#include "include/window.h"
#include "include/renderer.h"

int main(int argc, char *argv[]) {
    Window win;
    InitWindow(&win, 1280, 720, "test");

    Renderer renderer;
    InitRenderer(&renderer, "shaders/vertex1.glsl", "shaders/fragment1.glsl");

    Quad2dBuffer qb;
    Q2dBufInit(&qb);

    Quad2d quad = {
        .id = 1,
        .layer = LAYER_FOREGROUND,
        .a = {  0.0f,  1.0f, 0.0f, 0.0f },
        .b = {  1.0f,  1.0f, 1.0f, 0.0f },
        .c = {  0.0f,  0.0f, 0.0f, 1.0f },
        .d = {  1.0f,  0.0f, 1.0f, 1.0f },
    };

    Q2dBufPush(&qb, quad);

    UploadData(&renderer, &qb);
    
    while (!WindowShouldClose(&win)) {
        SetBackgroundColor(COLOR_CYAN);
        UseShader(&renderer, 0);
        Draw(&renderer, 0, qb.size * 6);
        UpdateWindow(&win);
    }

    Q2dBufFree(&qb);
    DestroyRenderer(&renderer);
    DestroyWindow(&win);
    return 0;
}