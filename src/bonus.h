#ifndef ARAYNOID_BONUS_H
#define ARAYNOID_BONUS_H

#include <stdbool.h>

#include "raylib.h"

#include "config.h"
#include "brick.h"


//
// TYPES
//
typedef enum BONUS {
    BONUS_NONE = '\0',
    BONUS_LASER = 'L',
    BONUS_ENLARGE = 'E',
    BONUS_CATCH = 'C',
    BONUS_SLOW = 'S',
    BONUS_BREAK = 'B',
    BONUS_DISRUPTION = 'D',
    BONUS_PLAYER = 'P'
} BONUS;

typedef struct bonus_t {
    BONUS type;
    Vector2 position;
    Color color;
} bonus_t;

//
// SHARED VARIABLES
//
#include "player.h"

extern bonus_t fallingBonus;
extern bool bonus_break;

//
// FUNCTIONS
//
void InitBonus();
void UpdateBonus();
void DrawBonus();

/**
 * Generates a bonus if none are already falling.
 *
 * @param x X coord of the bonus
 * @param y Y coord of the bonus
 */
void DestroyedBrickBonus(float x, float y);

#endif //ARAYNOID_BONUS_H
