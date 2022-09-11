#include "animation.h"

Animation *LoadAnimation(const char *filename, const AnimationParam params, float time)
{
    Animation *animation = malloc(sizeof(Animation));

    animation->spritemap = LoadTexture(filename);

    animation->params = params;

    StartTimer(&animation->timer, time);
    animation->currentFrame = params.direction == ANIMATION_DIRECTION_REVERSE ? params.totalFrames : 0;

    return animation;
}

void DrawAnimation(Animation *animation, const Vector2 position)
{
    // No animation
    if (animation == NULL) {
        return;
    }

    UpdateTimer(&animation->timer);

    // If timer is done
    // update current drawing frame
    // and restart timer
    if (TimerDone(&animation->timer)) {
        RestartTimer(&animation->timer);

        if (animation->params.direction == ANIMATION_DIRECTION_REVERSE) {
            animation->currentFrame--;

            if (animation->currentFrame < 0) {
                animation->currentFrame = animation->params.totalFrames;
            }
        } else {
            animation->currentFrame++;

            if (animation->currentFrame >= animation->params.totalFrames) {
                animation->currentFrame = 0;
            }
        }
    }

    Rectangle source = {
        animation->currentFrame*animation->params.size,
        0,
        (float) animation->params.size,
        (float) animation->params.size
    };

    DrawTexturePro(
        animation->spritemap,
        source,
        (Rectangle) {
            position.x,
            position.y,
            32, // TODO: Put this as parameter somewhere
            32 //   and this too
        },
        (Vector2) {0, 0},
        0,
        WHITE
    );

#ifdef DEBUG
    DrawText(
        TextFormat("%d/%d", animation->currentFrame, animation->params.totalFrames),
        position.x,
        position.y + 32,
        8,
        YELLOW
    );
#endif
}

void UnloadAnimation(Animation *animation)
{
    if (animation == NULL) {
        return;
    }

    UnloadTexture(animation->spritemap);

    free(animation);
}
