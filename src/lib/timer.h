#ifndef ARAYNOID_TIMER_H
#define ARAYNOID_TIMER_H

#include <stdbool.h>
#include <stddef.h>

#include "raylib.h"


// TYPES
typedef struct Timer {
    float initialLifetime;
    float lifetime;
} Timer;


// FUNCTIONS
void StartTimer(Timer *timer, float life);
void UpdateTimer(Timer *timer);
bool TimerDone(Timer *timer);
void RestartTimer(Timer *timer);


#endif //ARAYNOID_TIMER_H
