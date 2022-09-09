#ifndef ARAYNOID_ANIMATION_H
#define ARAYNOID_ANIMATION_H

#include <stdlib.h>

#include "raylib.h"


//
// TYPES
//

typedef enum AnimationDirection {
    ANIMATION_DIRECTION_FORWARD,
    ANIMATION_DIRECTION_PINGPONG,
    ANIMATION_DIRECTION_REVERSE
} AnimationDirection;

typedef struct Animation {
    Texture2D spritemap;
    AnimationDirection direction;
    int size;
} Animation;


//
// FUNCTIONS
//

Animation *LoadAnimation(const char *filename, AnimationDirection direction, int size);

void DrawAnimation(Animation *animation, Vector2 position);

void UnloadAnimation(Animation *animation);


#endif //ARAYNOID_ANIMATION_H
