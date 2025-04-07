#ifndef COLOR_H
#define COLOR_H

typedef struct {
    float r, g, b, a;
} Color;

// Grayscale
#define COLOR_WHITE      ((Color){1.0f, 1.0f, 1.0f, 1.0f})
#define COLOR_BLACK      ((Color){0.0f, 0.0f, 0.0f, 1.0f})
#define COLOR_GRAY       ((Color){0.5f, 0.5f, 0.5f, 1.0f})

// Primary Colors
#define COLOR_RED        ((Color){1.0f, 0.0f, 0.0f, 1.0f})
#define COLOR_GREEN      ((Color){0.0f, 1.0f, 0.0f, 1.0f})
#define COLOR_BLUE       ((Color){0.0f, 0.0f, 1.0f, 1.0f})

// Secondary Colors
#define COLOR_YELLOW     ((Color){1.0f, 1.0f, 0.0f, 1.0f})
#define COLOR_CYAN       ((Color){0.0f, 1.0f, 1.0f, 1.0f})
#define COLOR_MAGENTA    ((Color){1.0f, 0.0f, 1.0f, 1.0f})

// Extras
#define COLOR_ORANGE     ((Color){1.0f, 0.5f, 0.0f, 1.0f})
#define COLOR_PURPLE     ((Color){0.5f, 0.0f, 0.5f, 1.0f})
#define COLOR_TRANSPARENT ((Color){0.0f, 0.0f, 0.0f, 0.0f})

#endif