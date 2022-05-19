#include "bonus.h"

void InitBonus()
{
    fallingBonus = (bonus_t) {
        BONUS_NONE,
        {0, 0},
        BLANK,
    };
    bonus_break = false;
}

void UpdateBonus()
{
    if (fallingBonus.type == BONUS_NONE) return;

    fallingBonus.position.y += BONUS_FALL_SPEED;

    // Below player
    if (fallingBonus.position.y > player.position.y + player.position.height) {
        fallingBonus = (bonus_t) {BONUS_NONE, {0, 0}, BLANK};
    }

    // Player catches bonus
    if (CheckCollisionRecs(
        player.position,
        (Rectangle) {fallingBonus.position.x, fallingBonus.position.y, BRICK_WIDTH, BRICK_HEIGHT}
    )) {
        player.position.width = BASE_PLAYER_WIDTH;

        switch (fallingBonus.type) {
            case BONUS_ENLARGE:
                player.position.width *= 1.40f;
                break;
            case BONUS_SLOW:
                break;
            case BONUS_BREAK:
                bonus_break = true;
                break;
            case BONUS_DISRUPTION:
                HandleDisruption();
                break;
            case BONUS_PLAYER:
                player.lives++;
                break;
            default:
                break;
        }

        if (fallingBonus.type != BONUS_CATCH) {
            ball->catched = false;
        }

        player.bonus = fallingBonus.type;
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

        const float alphaX = acosf(ballptr->speed.x/BALL_SPEED);
        const float alphaY = asinf(-ballptr->speed.y/BALL_SPEED);

        left_ball->speed = (Vector2) {
            cosf(alphaX + PI/12)*BALL_SPEED,
            -sinf(alphaY + PI/12)*BALL_SPEED
        };
        left_ball->position = ballptr->position;
        left_ball->catched = false;
        left_ball->next = right_ball;

        right_ball->speed = (Vector2) {
            cosf(alphaX - PI/12)*BALL_SPEED,
            -sinf(alphaY - PI/12)*BALL_SPEED
        };
        right_ball->position = ballptr->position;
        right_ball->catched = false;
        right_ball->next = ballptr->next;

        ballptr->next = left_ball;
        ballptr = right_ball->next;
    }
}

void DestroyedBrickBonus(float x, float y)
{
    if (fallingBonus.type != BONUS_NONE) return;

    const int value = GetRandomValue(1, 7);
    BONUS bonus;
    Color color;

    switch (value) {
        case 1:
            bonus = BONUS_LASER;
            color = RED;
            break;
        case 2:
            bonus = BONUS_ENLARGE;
            color = BLUE;
            break;
        case 3:
            bonus = BONUS_CATCH;
            color = GREEN;
            break;
        case 4:
            bonus = BONUS_SLOW;
            color = ORANGE;
            break;
        case 5:
            bonus = BONUS_BREAK;
            color = VIOLET;
            break;
        case 6:
            bonus = BONUS_DISRUPTION;
            color = CYAN;
            break;
        case 7:
            bonus = BONUS_PLAYER;
            color = GRAY;
            break;
        default:
            bonus = BONUS_NONE;
            color = BLANK;
    }

    if (bonus == BONUS_NONE) return;

    fallingBonus = (bonus_t) {
        bonus,
        {x, y},
        color,
    };
}
