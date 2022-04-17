#ifndef ARAYNOID_GAME_H
#define ARAYNOID_GAME_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "level.h"
#include "ball.h"
#include "player.h"
#include "score.h"

//
// SHARED VARIABLES
//
extern bool pause;
extern bool borderless;

extern Font scoreFont;

extern bool showDebug;

#ifdef DEBUG
typedef struct levelDebug_t {
    bool debugging;
    char buffer[3];
    unsigned short index;
} levelDebug_t;

extern levelDebug_t lvlDebug;
#endif

//
// FUNCTIONS
//
void InitGame();
void UnloadGame();

void UpdateFrame();
void DrawFrame();
void DrawOutline();

void DrawDebug();

void ToggleBorderless();

#endif //ARAYNOID_GAME_H
