#ifndef ARAYNOID_BALL_H
#define ARAYNOID_BALL_H

#include <math.h>

#include "raylib.h"
#include "raymath.h"

#include "config.h"
#include "player.h"
#include "lib/timer.h"

//
// TYPES
//
typedef struct ball_t {
    Vector2 position;
    Vector2 speed;
    bool catched;
    struct ball_t *next;
} ball_t;

//
// SHARED VARIABLES
//
extern float BALL_SPEED;
extern float BALL_RADIUS;
extern ball_t *ball;
extern float ballOffset;
extern Timer ballSpeedTimer;

//
// FUNCTIONS
//
void InitBall();
void UpdateBall();
void DrawBall();
void DestroyBall();

int BallCount();

#endif //ARAYNOID_BALL_H
