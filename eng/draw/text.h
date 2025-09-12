#ifndef TEXT_H
#define TEXT_H

#include "type/vec.h"
#include "draw/draw.h"

typedef enum{
    CB_LEFT,
    CB_CENTER,
    CB_RIGHT,
} CBalignment;

typedef struct {
    int charW;
    int charH;
    char* chars;
    int* charGaps;
    int charAmt;
    CBtexture* atlas;
} CBfont;

void cbDrawText(CBfont* font, const char* text, int len, int fontSize, float x, float y, CBalignment align);

#endif
