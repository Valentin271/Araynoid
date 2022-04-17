#ifndef ARAYNOID_LEVEL_H
#define ARAYNOID_LEVEL_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "raylib.h"

#include "colors.h"
#include "config.h"
#include "brick.h"
#include "ball.h"
#include "utils.h"

//
// TYPES
//
typedef struct {
    unsigned short number;
    brick data[LEVEL_WIDTH][LEVEL_HEIGHT];
} level;

//
// VARIABLES
//
extern level currentLvl;
extern Font scoreFont;
extern short OUTLINE_WIDTH;

//
// FUNCTIONS
//
void LoadLevel(unsigned short number);
void UpdateLevel();
void DrawLevel();

bool IsLevelCleared();

#endif //ARAYNOID_LEVEL_H
