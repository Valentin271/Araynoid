#ifndef ARAYNOID_CONFIG_H
#define ARAYNOID_CONFIG_H

#include <math.h>

//
// WINDOW
//
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

//
// LEVEL
//
#define LEVEL_HEIGHT 14
#define LEVEL_WIDTH 11
#define BASE_OUTLINE_WIDTH 20
#define TOP_OFFSET 100

short OUTLINE_WIDTH;

//
// BRICKS
//
#define BASE_BRICK_WIDTH 40
#define BASE_BRICK_HEIGHT 18
#define BASE_LINE_THICK 1

int BRICK_WIDTH;
int BRICK_HEIGHT;
int LINE_THICK;

//
// BALL
//
#define BASE_BALL_SPEED 5.5f
#define BASE_BALL_RADIUS 5.0f

//
// PLAYER
//
#define BASE_PLAYER_WIDTH 70
#define BASE_PLAYER_HEIGHT 15

//
// MISC
//
#define MAX_BOUNCE_ANGLE (2*PI/5) // 72 degrees

#endif //ARAYNOID_CONFIG_H
