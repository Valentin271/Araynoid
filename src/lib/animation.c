#include "animation.h"

Animation *LoadAnimation(const char *filename, AnimationDirection direction, int size)
{
    Animation *animation = malloc(sizeof(Animation));

    animation->spritemap = LoadTexture(filename);
    animation->direction = direction;
    animation->size = size;

    return animation;
}

void DrawAnimation(Animation *animation, const Vector2 position)
{
    if (animation == NULL) {
        return;
    }

    Rectangle source = {
        0,
        0,
        (float) animation->size,
        (float) animation->size
    };

    DrawTextureRec(animation->spritemap, source, position, WHITE);
}

void UnloadAnimation(Animation *animation)
{
    UnloadTexture(animation->spritemap);

    free(animation);
}
