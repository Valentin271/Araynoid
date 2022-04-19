#include "ball.h"


void InitBall()
{
    BALL_SPEED = BASE_BALL_SPEED;
    BALL_RADIUS = BASE_BALL_RADIUS;

    ballOffset = 0.66f*player.position.width;

    ball.position = (Vector2) {150, 300};
    ball.speed = (Vector2) {cosf(PI/4)*BALL_SPEED, sinf(PI/4)*-BALL_SPEED};
    ball.catched = true;
}

void UpdateBall()
{
    ball.position.x += ball.speed.x;
    ball.position.y += ball.speed.y;

    // too far top
    if (ball.position.y - BALL_RADIUS < OUTLINE_WIDTH) {
        ball.speed.y *= -1;
        ball.position.y = OUTLINE_WIDTH + BALL_RADIUS;
    }

    // too far left
    if (ball.position.x - BALL_RADIUS < OUTLINE_WIDTH) {
        ball.speed.x *= -1;
        ball.position.x = OUTLINE_WIDTH + BALL_RADIUS;
    }

    // too far right
    if (ball.position.x + BALL_RADIUS > LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH) {
        ball.speed.x *= -1;
        ball.position.x = LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH - BALL_RADIUS;
    }

    // player collision
    if (CheckCollisionCircleRec(ball.position, BALL_RADIUS, player.position)) {
        ball.position.y = player.position.y - BALL_RADIUS;

        const float ballRelativeX = ball.position.x - player.position.x - player.position.width/2;
        const float bounceAngle = ballRelativeX*MAX_BOUNCE_ANGLE/(player.position.width/2) + PI/2;

        ball.speed.x = -cosf(bounceAngle)*BALL_SPEED;
        ball.speed.y = -sinf(bounceAngle)*BALL_SPEED;

        if (player.bonus == BONUS_CATCH) {
            ball.catched = true;
            ballOffset = ball.position.x - player.position.x;
        }
    }

    if (ball.catched) {
        ball.position = (Vector2) {player.position.x + ballOffset, player.position.y - BALL_RADIUS};
    }

    if (ball.position.y > player.position.y + player.position.height) {
        player.lives--;
        InitBall();
        InitBonus();
        player.bonus = BONUS_NONE;
    }
}

void DrawBall()
{
    DrawCircle(ball.position.x, ball.position.y, BALL_RADIUS, WHITE);

#ifdef DEBUG
    DrawLine(
            ball.position.x,
            ball.position.y,
            ball.position.x + ball.speed.x*3,
            ball.position.y + ball.speed.y*3,
            YELLOW
    );
#endif
}
