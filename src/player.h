#ifndef ARAYNOID_PLAYER_H
#define ARAYNOID_PLAYER_H

#include "raylib.h"

#include "config.h"

struct {
    int lives;
    Rectangle position;
} player;

void InitPlayer();
void UpdatePlayer();
void DrawPlayer();

#endif //ARAYNOID_PLAYER_H
