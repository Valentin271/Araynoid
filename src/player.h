#ifndef ARAYNOID_PLAYER_H
#define ARAYNOID_PLAYER_H

#include "raylib.h"

#include "config.h"
#include "utils.h"
#include "level.h"
#include "bonus.h"

//
// TYPES
//
typedef struct player_t {
    int lives;
    unsigned int score;
    Rectangle position;
    BONUS bonus;
} player_t;

//
// SHARED VARIABLES
//
extern player_t player;

//
// FUNCTIONS
//
void InitPlayer();
void UpdatePlayer();
void DrawPlayer();

#endif //ARAYNOID_PLAYER_H
