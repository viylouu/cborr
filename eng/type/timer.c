#include "timer.h"

#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "type/dyn.h"
#include <stdio.h>

dyn timers;

CBtimer* cbMakeTimer(float offset) {
    CBtimer* timer = malloc(sizeof(CBtimer));
    timer->time = offset;
    timer->delta = 0;
    timer->speed = 1;
    timer->index = timers.size;
    cbDynArrPushBack(&timers, &timer);
    return timer;
}

void cbDestroyTimer(CBtimer* timer) {
    if (!timer) { printf("cannot destroy a NULL timer!\n"); return; }

    for (size_t i = 0; i < timers.size; ++i) 
        if (*(CBtimer**)cbDynArrIndex(&timers, i) == timer) {
            *(CBtimer**)cbDynArrIndex(&timers,i) = *(CBtimer**)cbDynArrIndex(&timers, timers.size-1);
            timers.size--;
            break;
        }
    //void* toDest = cbDynArrIndex(&timers, timer->index);
    //free(toDest);
    //toDest = 0;
    free(timer);
}

void cbInitTimers(float time) {
    cbDynArrInit(&timers, sizeof(CBtimer*));

    cbMakeTimer(time);
    cbMakeTimer(time);
}

void cbEndTimers() {
    cbDestroyTimer((CBtimer*)cbDynArrIndex(&timers, 0));
    cbDestroyTimer((CBtimer*)cbDynArrIndex(&timers, 1));
    cbDynArrFree(&timers);
}

void cbUpdateTimers() {
    float time = (float)glfwGetTime();

    CBtimer* last = (CBtimer*)cbDynArrIndex(&timers, 1);
    CBtimer* main = (CBtimer*)cbDynArrIndex(&timers, 0);
    main->time = time;
    main->delta = time - last->time;
    last->time = time;

    if(timers.size > 2)
        for (int i = 2; i < timers.size; ++i) {
            CBtimer* this = (CBtimer*)cbDynArrIndex(&timers, i);
            this->delta = this->speed * main->delta;
            this->time += this->delta;
        }
}
