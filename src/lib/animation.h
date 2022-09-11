#ifndef ARAYNOID_ANIMATION_H
#define ARAYNOID_ANIMATION_H

#include <stdlib.h>

#include "raylib.h"

#include "timer.h"


//
// TYPES
//

typedef enum AnimationDirection {
    ANIMATION_DIRECTION_FORWARD,
    ANIMATION_DIRECTION_PINGPONG,
    ANIMATION_DIRECTION_REVERSE
} AnimationDirection;

typedef struct AnimationParam {
    unsigned int size;
    AnimationDirection direction;
    unsigned short totalFrames;
} AnimationParam;

typedef struct Animation {
    Texture2D spritemap;
    AnimationParam params;
    unsigned short currentFrame; // starts at 0
    Timer timer;
} Animation;


//
// FUNCTIONS
//

Animation *LoadAnimation(const char *filename, AnimationParam params, float time);

void DrawAnimation(Animation *animation, Vector2 position);

void UnloadAnimation(Animation *animation);


#endif //ARAYNOID_ANIMATION_H
