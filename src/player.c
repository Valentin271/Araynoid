#include "player.h"

void InitPlayer()
{
    player.lives = 2;
    player.score = 0;
    player.position = (Rectangle) {0, GetScreenHeight() - 30, BASE_PLAYER_WIDTH, BASE_PLAYER_HEIGHT};
    player.bonus = BONUS_CATCH;
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
        if (bonus_break) {
            LoadLevel(currentLvl.number + 1);
        }
        player.position.x = LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH - player.position.width;
    }

    // MouseButtonDown so player can stay clicked
    if (ball.catched && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        ball.catched = false;
    }
}

void DrawPlayer()
{
    DrawRectangleRec(player.position, WHITE);
    DrawT(TextFormat("%d", player.lives), OUTLINE_WIDTH + 2, GetScreenHeight() - 10, 8, RAYWHITE);

#ifdef DEBUG
    DrawT((char *) &player.bonus, player.position.x, player.position.y + player.position.height, 12, YELLOW);
#endif
}
