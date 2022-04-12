#ifndef ARAYNOID_GAME_H
#define ARAYNOID_GAME_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "level.h"
#include "ball.h"
#include "player.h"


level currentLvl;
bool pause;
bool borderless;

bool showDebug;

#ifdef DEBUG
struct {
    bool debugging;
    char buffer[3];
    unsigned short index;
} lvlDebug;
#endif

void InitGame();

void UpdateFrame();
void DrawFrame();
void DrawOutline();

void DrawDebug();

void ToggleBorderless();

#endif //ARAYNOID_GAME_H
