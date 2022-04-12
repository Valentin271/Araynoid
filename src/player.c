#include "player.h"

void InitPlayer()
{
    player.lives = 2;
    player.position = (Rectangle) {0, GetScreenHeight() - 30, BASE_PLAYER_WIDTH, BASE_PLAYER_HEIGHT};
}

void UpdatePlayer()
{
    player.position.x = GetMouseX() - player.position.width/2;

    // too far left
    if (player.position.x < OUTLINE_WIDTH) {
        player.position.x = OUTLINE_WIDTH;
    }

    // too far right
    if (player.position.x + player.position.width > LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH) {
        player.position.x = LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH - player.position.width;
    }
}

void DrawPlayer()
{
    DrawRectangleRec(player.position, WHITE);
}
