#include "ball.h"


void InitBall()
{
    BALL_SPEED = BASE_BALL_SPEED;
    BALL_RADIUS = BASE_BALL_RADIUS;

    ballOffset = 0.66f*player.position.width;

    DestroyBall();

    ball = malloc(sizeof(ball_t));

    ball->position = (Vector2) {150, 300};
    ball->speed = (Vector2) {cosf(1.35f)*BALL_SPEED, sinf(1.35f)*-BALL_SPEED};
    ball->catched = true;
    ball->next = NULL;
}

void UpdateBall()
{
    ball_t *ballptr = ball;
    ball_t *lastptr = NULL;

    while (ballptr != NULL) {
        ballptr->position.x += ballptr->speed.x;
        ballptr->position.y += ballptr->speed.y;

        // too far top
        if (ballptr->position.y - BALL_RADIUS < OUTLINE_WIDTH) {
            ballptr->speed.y *= -1;
            ballptr->position.y = OUTLINE_WIDTH + BALL_RADIUS;
        }

        // too far left
        if (ballptr->position.x - BALL_RADIUS < OUTLINE_WIDTH) {
            ballptr->speed.x *= -1;
            ballptr->position.x = OUTLINE_WIDTH + BALL_RADIUS;
        }

        // too far right
        if (ballptr->position.x + BALL_RADIUS > LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH) {
            ballptr->speed.x *= -1;
            ballptr->position.x = LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH - BALL_RADIUS;
        }

        // player collision
        if (CheckCollisionCircleRec(ballptr->position, BALL_RADIUS, player.position)) {
            ballptr->position.y = player.position.y - BALL_RADIUS;

            const float ballRelativeX = ballptr->position.x - player.position.x - player.position.width/2;
            const float bounceAngle = ballRelativeX*MAX_BOUNCE_ANGLE/(player.position.width/2) + PI/2;

            ballptr->speed.x = -cosf(bounceAngle)*BALL_SPEED;
            ballptr->speed.y = -sinf(bounceAngle)*BALL_SPEED;

            if (player.bonus == BONUS_CATCH) {
                ballptr->catched = true;
                ballOffset = ballptr->position.x - player.position.x;
            }
        }

        if (ballptr->catched) {
            ballptr->position = (Vector2) {player.position.x + ballOffset, player.position.y - BALL_RADIUS};
        }

        // ball under player
        if (ballptr->position.y > player.position.y + player.position.height) {
            if (BallCount() == 1) {
                player.lives--;
                InitBall();
                InitBonus();
                player.bonus = BONUS_NONE;
            } else {
                if (lastptr == NULL) {
                    ball = ballptr->next;
                    free(ballptr);
                    ballptr = ball;
                } else {
                    lastptr->next = ballptr->next;
                    free(ballptr);
                    ballptr = lastptr;
                }
            }
        }

        lastptr = ballptr;
        ballptr = ballptr->next;
    }
}

void DrawBall()
{
    ball_t *ballptr = ball;

    while (ballptr != NULL) {
        DrawCircle(ballptr->position.x, ballptr->position.y, BALL_RADIUS, WHITE);

#ifdef DEBUG
        DrawLine(
            ballptr->position.x,
            ballptr->position.y,
            ballptr->position.x + ballptr->speed.x*3,
            ballptr->position.y + ballptr->speed.y*3,
            YELLOW
        );
#endif

        ballptr = ballptr->next;
    }
}

void DestroyBall()
{
    // deleting every balls
    ball_t *tmp = NULL;
    while (ball != NULL) {
        tmp = ball->next;
        free(ball);
        ball = tmp;
    }
}

int BallCount()
{
    int count = 1;

    ball_t *ballptr = ball->next;

    while (ballptr != NULL) {
        ++count;
        ballptr = ballptr->next;
    }

    return count;
}