#ifndef ARAYNOID_BALL_H
#define ARAYNOID_BALL_H

#include <math.h>
#include <stdbool.h>

#include "raylib.h"

#include "config.h"
#include "player.h"

//
// TYPES
//
typedef struct ball_t {
    bool catch;
    Vector2 position;
    Vector2 speed;
} ball_t;

//
// SHARED VARIABLES
//
extern float BALL_SPEED;
extern float BALL_RADIUS;
extern ball_t ball;

//
// FUNCTIONS
//
void InitBall();
void UpdateBall();
void DrawBall();

#endif //ARAYNOID_BALL_H
