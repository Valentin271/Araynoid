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

#define SCORE_FONTSIZE 20

//
// BRICKS
//
#define BASE_BRICK_WIDTH 46
#define BASE_BRICK_HEIGHT 24

//
// BONUS
//
#define BONUS_FALL_SPEED 4.0f

//
// BALL
//
#define BASE_BALL_SPEED 6.0f
#define BASE_BALL_RADIUS 7.0f

//
// PLAYER
//
#define BASE_PLAYER_WIDTH 64
#define BASE_PLAYER_HEIGHT 16

#define LASER_SPEED 24.0f
#define LASER_WIDTH 2
#define LASER_HEIGHT 12

//
// MISC
//
#define MAX_BOUNCE_ANGLE (2*PI/5) // 72 degrees

#endif //ARAYNOID_CONFIG_H
