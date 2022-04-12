#ifndef ARAYNOID_BRICK_H
#define ARAYNOID_BRICK_H

#include "raylib.h"

#include "colors.h"

#define BRICK_UNBREAKABLE  -1
#define BRICK_TRANSPARENT  -2
#define BRICK_DESTROYED     0

//
// TYPES
//
typedef enum {
    BRICK_CYAN = '0',   // 70  points
    BRICK_RED = '1',    // 80
    BRICK_VIOLET = '2', // 90
    BRICK_WHITE = '3',  // 100
    BRICK_GREEN = '4',  // 110
    BRICK_BLUE = '5',   // 120
    BRICK_YELLOW = '6', // 130
    BRICK_SILVER = '7', // lvl2 100
    BRICK_GOLD = '8',
    BRICK_NONE = ' '
} BRICK_CODE;

typedef struct {
    char code;        // Brick sotage code
    short hitsLeft;   // Number of hits left
} brick;


//
// FUNCTIONS
//
Color brickColor(const brick *brk);

unsigned int brickPoints(const brick *brk);

#endif //ARAYNOID_BRICK_H
