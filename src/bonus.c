#include "bonus.h"

void InitBonus()
{
    fallingBonus = (bonus_t) {
        BONUS_NONE,
        {0, 0},
        BLANK,
    };

    StartTimer(&fallingBonusTimer, BONUS_FALL_TIME);
}

void UpdateBonus()
{
    if (fallingBonus.type == BONUS_NONE) return;
    UpdateTimer(&fallingBonusTimer);

    if (TimerDone(&fallingBonusTimer)) {
        fallingBonus.position.y += BONUS_FALL_SPEED;
        RestartTimer(&fallingBonusTimer);
    }

    // Below player
    if (fallingBonus.position.y > player.position.y + player.position.height) {
        fallingBonus = (bonus_t) {BONUS_NONE, {0, 0}, BLANK};
    }

    // Player catches bonus
    if (CheckCollisionRecs(
        player.position,
        (Rectangle) {fallingBonus.position.x, fallingBonus.position.y, BRICK_WIDTH, BRICK_HEIGHT}
    )) {
        // resets enlarge
        player.position.width = BASE_PLAYER_WIDTH;
        player.bonus = BONUS_NONE;

        switch (fallingBonus.type) {
            case BONUS_ENLARGE:
                player.position.width *= 1.40f;
                break;
            case BONUS_DISRUPTION:
                player.bonus = fallingBonus.type;
                HandleDisruption();
                break;
            case BONUS_PLAYER:
                player.lives++;
                break;
            case BONUS_SLOW:
                HandleSlow();
                break;
            case BONUS_BREAK:
            case BONUS_LASER:
            case BONUS_CATCH:
                player.bonus = fallingBonus.type;
                break;
            default:
                break;
        }

        if (fallingBonus.type != BONUS_CATCH) {
            ball->catched = false;
        }

        player.score += 1000;
        fallingBonus = (bonus_t) {BONUS_NONE, {0, 0}, BLANK};
    }
}

void DrawBonus()
{
    if (fallingBonus.type == BONUS_NONE) return;

    DrawRectangleRounded(
        (Rectangle) {
            fallingBonus.position.x,
            fallingBonus.position.y,
            BRICK_WIDTH,
            BRICK_HEIGHT
        },
        0.5f,
        4,
        fallingBonus.color
    );

    const Vector2 textSize = MeasureT((const char *) &fallingBonus.type, 16);

    DrawT(
        (const char *) &fallingBonus.type,
        fallingBonus.position.x + BRICK_WIDTH/2 - textSize.x/2,
        fallingBonus.position.y + BRICK_HEIGHT/2 - textSize.y/2,
        16,
        WHITE
    );
}

void HandleDisruption()
{
    ball_t *ballptr = ball;
    ball_t *left_ball, *right_ball;

    while (ballptr != NULL) {
        left_ball = malloc(sizeof(ball_t));
        right_ball = malloc(sizeof(ball_t));

        left_ball->speed = Vector2Rotate(ballptr->speed, PI/12);
        left_ball->position = ballptr->position;
        left_ball->catched = false;
        left_ball->next = right_ball;

        right_ball->speed = Vector2Rotate(ballptr->speed, -PI/12);
        right_ball->position = ballptr->position;
        right_ball->catched = false;
        right_ball->next = ballptr->next;

        ballptr->next = left_ball;
        ballptr = right_ball->next;
    }
}

void HandleSlow()
{
    const float oldSpeed = BALL_SPEED;

    BALL_SPEED -= 2;
    if (BALL_SPEED < BALL_MIN_SPEED) {
        BALL_SPEED = BALL_MIN_SPEED;
    }

    // There is no bonus while disrupt is active,
    // so no need to loop over balls
    ball->speed = Vector2Divide(ball->speed, (Vector2) {oldSpeed, oldSpeed});
    ball->speed = Vector2Multiply(ball->speed, (Vector2) {BALL_SPEED, BALL_SPEED});
}

void DestroyedBrickBonus(float x, float y)
{
    if (fallingBonus.type != BONUS_NONE || player.bonus == BONUS_DISRUPTION || player.bonus == BONUS_BREAK) {
        return;
    }

    // 1 chance out of 4 to have a bonus
    if (GetRandomValue(1, 4) != 1) {
        return;
    }

    const int value = GetRandomValue(1, 100);
    BONUS bonus;
    Color color;

    if (value <= 12) {
        bonus = BONUS_LASER;
        color = RED;
    } else if (value <= 26) {
        bonus = BONUS_ENLARGE;
        color = BLUE;
    } else if (value <= 44) {
        bonus = BONUS_CATCH;
        color = GREEN;
    } else if (value <= 63) {
        bonus = BONUS_SLOW;
        color = ORANGE;
    } else if (value <= 73) {
        bonus = BONUS_BREAK;
        color = VIOLET;
    } else if (value <= 90) {
        bonus = BONUS_DISRUPTION;
        color = CYAN;
    } else if (value <= 100) {
        bonus = BONUS_PLAYER;
        color = GRAY;
    } else {
        return;
    }

    fallingBonus = (bonus_t) {
        bonus,
        {x, y},
        color,
    };
}
