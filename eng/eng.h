#ifndef ENG_H
#define ENG_H

#include "draw/tex.h"
#include "draw/shad.h"
#include "draw/draw.h"
#include "type/mat.h"
#include "type/dyn.h"
//#include "gl/gl.h"

extern int actWidth;
extern int actHeight;

extern float CB_WIDTH;
extern float CB_HEIGHT;

extern dyn times;
extern dyn deltas;
extern dyn speeds;

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
