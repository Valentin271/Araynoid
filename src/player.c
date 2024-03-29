#include "player.h"

void InitPlayer()
{
    player.lives = 2;
    player.score = 0;
    player.position = (Rectangle) {
        0,
        GetScreenHeight() - BASE_PLAYER_HEIGHT - 50,
        BASE_PLAYER_WIDTH,
        BASE_PLAYER_HEIGHT
    };
    player.bonus = BONUS_NONE;

    laser.active = false;

    StartTimer(&laserTimer, LASER_TIME);
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
        if (player.bonus == BONUS_BREAK) {
            ChangeLevel(currentLvl.number + 1);
        }
        player.position.x = LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH - player.position.width;
    }

    // MouseButtonDown so player can stay clicked
    if (ball->catched && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && TimerDone(&levelBegin)) {
        ball->catched = false;
    }

    if (laser.active) {
        UpdateTimer(&laserTimer);
        if (TimerDone(&laserTimer)) {
            laser.l_laser.y -= LASER_SPEED;
            laser.r_laser.y -= LASER_SPEED;
        }

        // Laser out of bounds
        if (laser.l_laser.y < OUTLINE_WIDTH) {
            laser.active = false;
        } else {
            RestartTimer(&laserTimer);
        }
    }

    // Laser shooting
    if (player.bonus == BONUS_LASER && !laser.active && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        RestartTimer(&laserTimer);

        laser.l_laser = (Rectangle) {
            player.position.x + 0.18f*player.position.width,
            player.position.y - LASER_HEIGHT,
            LASER_WIDTH,
            LASER_HEIGHT
        };
        laser.r_laser = (Rectangle) {
            player.position.x + 0.82f*player.position.width,
            player.position.y - LASER_HEIGHT,
            LASER_WIDTH,
            LASER_HEIGHT
        };
        laser.active = true;
    }
}

void DrawPlayer()
{
    // Player
    if (TimerDone(&levelBegin)) {
        DrawTexturePro(
            player.bonus == BONUS_LASER ? playerLaserSprite : playerSprite,
            (Rectangle) {0, 0, 64, 16},
            player.position,
            (Vector2) {0, 0},
            0,
            WHITE
        );
    }

    // Lives, display 5 max
    for (int i = 0; i < player.lives && i < 5; ++i) {
        DrawTexturePro(
            playerSprite,
            (Rectangle) {0, 0, 64, 16},
            (Rectangle) {
                OUTLINE_WIDTH + 20 + i*BASE_PLAYER_WIDTH/2 + i*10,
                GetScreenHeight() - 10 - BASE_PLAYER_HEIGHT/2,
                BASE_PLAYER_WIDTH/2.0f,
                BASE_PLAYER_HEIGHT/2.0f,
            },
            (Vector2) {0, 0},
            0,
            WHITE
        );
    }

    // Lasers
    if (laser.active) {
        DrawRectangleRec(laser.l_laser, WHITE);
        DrawRectangleRec(laser.r_laser, WHITE);
    }

#ifdef DEBUG
    DrawT((char *) &player.bonus, player.position.x, player.position.y + player.position.height, 12, YELLOW);
#endif
}

void ResetPlayer()
{
    player.position.width = BASE_PLAYER_WIDTH;

    player.bonus = BONUS_NONE;
    laser.active = false;
}