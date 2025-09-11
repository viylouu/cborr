#ifndef TIME_H
#define TIME_H

typedef struct {
    float speed;
    float time;
    float delta;
} CBtime;

CBtime* cbMakeTimer(float offset);
void cbDestroyTimer(CBtime* timer);

#endif
