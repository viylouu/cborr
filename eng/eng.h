#ifndef ENG_H
#define ENG_H

#include "draw/draw.h"

extern int actWidth;
extern int actHeight;

typedef void (*func)(void);

int cbMain(
    char* title,
    int width,
    int height,
    func init,
    func update,
    func render,
    func clean
);

#endif
