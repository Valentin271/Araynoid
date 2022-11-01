#ifndef ARAYNOID_SCORE_H
#define ARAYNOID_SCORE_H

#include <string.h>

#include "config.h"
#include "player.h"
#include "utils.h"
#include "level.h"


//
// TYPES
//
typedef struct {
    char *player_name;
    unsigned short round;
    unsigned int score;
} score_t;

typedef struct {
    score_t *data;
    size_t size;
} score_array_t;


//
// VARIABLES
//
extern score_array_t scores;


//
// FUNCTIONS
//
void DrawScore();

// TODO: implement score functions
void LoadScore();
void AddScore();
void SortScore();
score_t FirstScore();
void WriteScore();
void UnloadScore();

#endif //ARAYNOID_SCORE_H
