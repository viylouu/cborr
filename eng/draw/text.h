#ifndef TEXT_H
#define TEXT_H

#include "../type/vec.h"
#include "draw.h"

typedef enum{
    CB_LEFT,
    CB_CENTER,
    CB_RIGHT,
} CBalignment;

void cBDrawText2d(CBtexture* tex, char txt[], int fontSize, vec2 pos, CBalignment align);

#endif