#include "time.h"

#include "type/dyn.h"
#include <stdio.h>

dyn timers;

CBtime* cbMakeTimer(float offset) {
    CBtime* timer = malloc(sizeof(CBtime));
    timer->time = offset;
    timer->delta = 0;
    timer->speed = 1;
    cbDynArrPushBack(&timers, timer);
    return timer;
}

void cbDestroyTimer(CBtime* timer) {
    if (timer == NULL) { printf("cannot destroy a NULL timer!\n"); return; }
    for (int i = 0; i < timers.size; ++i)
        if (&timers[i] == timer)
            free(&timers[i]);
    free(timer);
}
