#ifndef ARAYNOID_UTILS_H
#define ARAYNOID_UTILS_H

#include <stdlib.h>

#include "raylib.h"

//
// TYPES
//
typedef enum RECT_SIDE {
    RECT_SIDE_NONE = 0,
    RECT_SIDE_BOTTOM = 1,
    RECT_SIDE_LEFT = 2,
    RECT_SIDE_TOP = 4,
    RECT_SIDE_RIGHT = 8,
} RECT_SIDE;

//
// VARIABLES
//
extern Font scoreFont;

//
// FUNCTIONS
//
/**
 * Check for specific side collision between a rect and a circle.
 *
 * @param rect Rectangle to check
 * @param sides Rectangle sides to check
 * @param center Circle center
 * @param radius Circle radius
 * @return The side with collision
 */
RECT_SIDE CheckCollisionRectSideCircle(Rectangle rect, RECT_SIDE sides, Vector2 center, float radius);

/**
 * Draw text with game default font (Press start 2P).
 *
 * @param text Text to draw
 * @param x Text position in X
 * @param y Text position in Y
 * @param fontSize Font size
 * @param color Text color
 */
void DrawT(const char *text, float x, float y, float fontSize, Color color);

/**
 * Measure text size according to game default font (Press start 2P)
 *
 * @param text Text to measure
 * @param fontSize Font size
 * @return Text size in X and Y
 */
Vector2 MeasureT(const char *text, float fontSize);

#endif //ARAYNOID_UTILS_H
