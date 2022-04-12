#ifndef ARAYNOID_BALL_H
#define ARAYNOID_BALL_H

#include <math.h>
#include <stdbool.h>

#include "raylib.h"

#include "config.h"
#include "player.h"

//
// VARIABLES
//
float BALL_SPEED;
float BALL_RADIUS;

//
// TYPES
//
struct {
    bool catch;
    Vector2 position;
    Vector2 speed;
} ball;

//
// FUNCTIONS
//
void InitBall();
void UpdateBall();
void DrawBall();

#endif //ARAYNOID_BALL_H
