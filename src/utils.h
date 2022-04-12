#ifndef ARAYNOID_UTILS_H
#define ARAYNOID_UTILS_H

#include <stdlib.h>

#include "raylib.h"

typedef enum {
    RECT_SIDE_NONE = 0,
    RECT_SIDE_BOTTOM = 1,
    RECT_SIDE_LEFT = 2,
    RECT_SIDE_TOP = 4,
    RECT_SIDE_RIGHT = 8,
} RECT_SIDE;

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

#endif //ARAYNOID_UTILS_H
