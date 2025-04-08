#include "include/noctyra2d.h"

int main(int argc, char *argv[]) {
    Window win;
    InitWindow(&win, 1280, 720, "test");

    Renderer renderer;
    InitRenderer(&renderer, "shaders/vertex1.glsl", "shaders/fragment1.glsl");

    Quad2dBuffer qb;
    Q2dBufInit(&qb);

    Texture t = LoadTexture("example/assets/nyan.jpg");

    Sprite s = {
        .pos = { 400.0f, 400.0f },
        .size = { 256.0f, 256.0f },
        .id = 0,
        .layer = LAYER_PLAYER,
        .uv_min = { 0.0f, 0.0f },
    };

    PushSprite(s, ScreenSize(&win), &qb);

    UploadData(&renderer, &qb);
    
    while (!WindowShouldClose(&win)) {
        SetBackgroundColor(COLOR_CYAN);
        UseShader(&renderer, 0);
        Draw(&renderer, 0, qb.size * 6, t.id);
        UpdateWindow(&win);
    }

    Q2dBufFree(&qb);
    FreeTexture(&t);
    DestroyRenderer(&renderer);
    DestroyWindow(&win);
    return 0;
}