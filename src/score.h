#ifndef ARAYNOID_SCORE_H
#define ARAYNOID_SCORE_H


#include "config.h"
#include "player.h"
#include "utils.h"
#include "level.h"

typedef struct {
    char *player_name; // TODO: max char ?
    unsigned short round;
    unsigned int score;
} score_t;

void DrawScore();

// TODO: implement score functions
void LoadScore();
void AddScore();
void SortScore();
score_t FirstScore();
void WriteScore();
void UnloadScore();

#endif //ARAYNOID_SCORE_H
