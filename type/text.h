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
    CBtexture* atlas;
} CBfont;

CBfont* cbLoadFont(const char* file, int charW, int charH);
void cbUnloadFont(CBfont* font);
void cbText(CBfont* font, const char* text, int fontSize, float x, float y);

#endif
