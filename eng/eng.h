#ifndef ENG_H
#define ENG_H

#include "draw/tex.h"
#include "draw/shad.h"
#include "draw/draw.h"
#include "type/mat.h"

extern int actWidth;
extern int actHeight;

extern float CB_WIDTH;
extern float CB_HEIGHT;

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
