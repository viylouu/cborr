#include "timer.h"

#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "type/dyn.h"
#include <stdio.h>

CBtimer* cbTime;

dyn timers;

CBtimer* cbMakeTimer(float offset) {
    CBtimer* timer = malloc(sizeof(CBtimer));
    timer->time = offset;
    timer->delta = 0;
    timer->speed = 1;
    timer->index = timers.size;
    cbDynArrPushBack(&timers, timer);
    return timer;
}

void cbDestroyTimer(CBtimer* timer) {
    if (!timer) { printf("cannot destroy a NULL timer!\n"); return; }

    for (size_t i = 0; i < timers.size; ++i) 
        if ((CBtimer*)cbDynArrIndex(&timers, i) == timer) {
            *(CBtimer*)cbDynArrIndex(&timers, i) = *(CBtimer*)cbDynArrIndex(&timers, timers.size-1);
            timers.size--;
            break;
        }

    free(timer);
}

void cbInitTimers(float time) {
    cbDynArrInit(&timers, sizeof(CBtimer));

    // bro...
    cbMakeTimer(time);
    cbTime = cbMakeTimer(time);
}

void cbEndTimers() {
    cbDestroyTimer(cbTime);
    cbDestroyTimer((CBtimer*)cbDynArrIndex(&timers, 0));
    cbDynArrFree(&timers);
}

void cbUpdateTimers() {
    float time = (float)glfwGetTime();

    CBtimer* state = (CBtimer*)cbDynArrIndex(&timers, 0);
    state->delta = time - state->time;
    state->time = time;

    for (int i = 1; i < timers.size; ++i) {
        CBtimer* this = (CBtimer*)cbDynArrIndex(&timers, i);
        this->delta = this->speed * state->delta;
        this->time += this->delta;
    }
}
