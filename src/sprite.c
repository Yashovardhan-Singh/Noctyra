#include "include/sprite.h"

#include "vendor/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void PushSprite(Sprite s, Vec2 screenSize, Quad2dBuffer* qb) {
    Quad2d q = {0}; // Zero Init

    q.layer = s.layer;
    q.id = s.id;

    f32 x = s.pos.x;
    f32 y = s.pos.y;
    f32 w = s.size.x;
    f32 h = s.size.y;

    // Convert To NDC
    f32 xa = PixelToNdcX(x, screenSize.x);
    f32 ya = PixelToNdcY(y, screenSize.y);
    f32 xb = PixelToNdcX(x + w, screenSize.x);
    f32 yb = PixelToNdcY(y + h, screenSize.y);

    // Top-Left
    q.a = (Vertex){ xa, ya, 0.0f, 0.0f };

    // Top-Right
    q.b = (Vertex){ xb, ya, 1.0, 0.0f };

    // Bottom-Left
    q.c = (Vertex){ xa, yb, 0.0f, 1.0 };

    // Bottom-Right
    q.d = (Vertex){ xb, yb, 1.0, 1.0 };

    Q2dBufPush(qb, q);
}
