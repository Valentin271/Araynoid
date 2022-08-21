#ifndef ARAYNOID_PLAYER_H
#define ARAYNOID_PLAYER_H

#include "raylib.h"

#include "config.h"
#include "utils.h"
#include "level.h"
#include "bonus.h"
#include "lib/timer.h"

//
// TYPES
//
typedef struct player_t {
    int lives;
    unsigned int score;
    Rectangle position;
    BONUS bonus;
} player_t;

typedef struct laser_t {
    Rectangle l_laser;
    Rectangle r_laser;
    bool active;
} laser_t;

//
// SHARED VARIABLES
//
extern player_t player;
extern laser_t laser;
extern Texture2D playerSprite;
extern Texture2D playerLaserSprite;
extern Timer laserTimer;

//
// FUNCTIONS
//
void InitPlayer();
void UpdatePlayer();
void DrawPlayer();

/**
 * Resets the player size and bonus.
 * Also resets the laser.
 */
void ResetPlayer();

#endif //ARAYNOID_PLAYER_H
