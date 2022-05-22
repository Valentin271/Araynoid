#include "timer.h"

void StartTimer(Timer *timer, float life)
{
    if (timer != NULL) {
        timer->lifetime = life;
    }
}

void UpdateTimer(Timer *timer)
{
    if (timer != NULL && timer->lifetime > 0) {
        timer->lifetime -= GetFrameTime();
    }
}

bool TimerDone(Timer *timer)
{
    return timer->lifetime <= 0;
}