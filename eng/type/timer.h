#ifndef TIMER_H
#define TIMER_H

#include <stdlib.h>

typedef struct {
    float speed;
    float time;
    float delta;
    size_t index;
} CBtimer;

CBtimer* cbMakeTimer(float offset);
void cbDestroyTimer(CBtimer* timer);
void cbInitTimers(float time);
void cbEndTimers();
void cbUpdateTimers();

#endif
