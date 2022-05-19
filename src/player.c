#include "player.h"

void InitPlayer()
{
    player.lives = 2;
    player.score = 0;
    player.position = (Rectangle) {0, GetScreenHeight() - 30, BASE_PLAYER_WIDTH, BASE_PLAYER_HEIGHT};
    player.bonus = BONUS_NONE;

    laser.active = false;
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
    if (ball->catched && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        ball->catched = false;
    }

    if (laser.active) {
        laser.l_laser.y -= LASER_SPEED;
        laser.r_laser.y -= LASER_SPEED;

        // Laser out of bounds
        if (laser.l_laser.y < OUTLINE_WIDTH) {
            laser.active = false;
        }
    }

    // Laser shooting
    if (player.bonus == BONUS_LASER && !laser.active && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        laser.l_laser = (Rectangle) {
            player.position.x + 0.2f*player.position.width,
            player.position.y,
            LASER_WIDTH,
            LASER_HEIGHT
        };
        laser.r_laser = (Rectangle) {
            player.position.x + 0.8f*player.position.width,
            player.position.y,
            LASER_WIDTH,
            LASER_HEIGHT
        };
        laser.active = true;
    }
}

void DrawPlayer()
{
    DrawRectangleRec(player.position, WHITE);
    DrawT(TextFormat("%d", player.lives), OUTLINE_WIDTH + 2, GetScreenHeight() - 10, 8, RAYWHITE);

    if (laser.active) {
        DrawRectangleRec(laser.l_laser, WHITE);
        DrawRectangleRec(laser.r_laser, WHITE);
    }

#ifdef DEBUG
    DrawT((char *) &player.bonus, player.position.x, player.position.y + player.position.height, 12, YELLOW);
#endif
}
