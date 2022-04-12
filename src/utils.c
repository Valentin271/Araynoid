#include "utils.h"

RECT_SIDE CheckCollisionRectSideCircle(Rectangle rect, RECT_SIDE sides, Vector2 center, float radius)
{
    // TODO: Check collision between line and circle, not flat rect

    if (sides & RECT_SIDE_BOTTOM) {
        const Rectangle bottom = {rect.x, rect.y + rect.height, rect.width, 0};
        if (CheckCollisionCircleRec(center, radius, bottom)) {
            return RECT_SIDE_BOTTOM;
        }
    }

    if (sides & RECT_SIDE_LEFT) {
        const Rectangle left = {rect.x, rect.y, 0, rect.height};
        if (CheckCollisionCircleRec(center, radius, left)) {
            return RECT_SIDE_LEFT;
        }
    }

    if (sides & RECT_SIDE_TOP) {
        const Rectangle top = {rect.x, rect.y, rect.width, 0};
        if (CheckCollisionCircleRec(center, radius, top)) {
            return RECT_SIDE_TOP;
        }
    }

    if (sides & RECT_SIDE_RIGHT) {
        const Rectangle right = {rect.x + rect.width, rect.y, 0, rect.height};
        if (CheckCollisionCircleRec(center, radius, right)) {
            return RECT_SIDE_RIGHT;
        }
    }

    return RECT_SIDE_NONE;
}
