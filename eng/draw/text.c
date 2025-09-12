#include "text.h"

#include "draw/tex.h"
#include "type/vec.h"
#include "eng.h"
#include "draw/draw.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

CBfont* cbLoadFont(const char* file, int charW, int charH) {
    CBfont* fnt = malloc(sizeof(CBfont));
    fnt->charW = charW;
    fnt->charH = charH;
    fnt->atlas = cbLoadTexture(file);

    return fnt;
}

void cbUnloadFont(CBfont* font) {
    free(font);
}

void cbDrawText(CBfont* font, const char* text, int fontSize, float x, float y) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char cur = text[i];        
        int sx = cur >> 4;
        int sy = cur & 0xF;

        cbTex(
            font->atlas, 
            x + i * font->charW * fontSize, 
            y, 
            font->charW * fontSize, 
            font->charH * fontSize, 
            sx * font->charW, 
            sy * font->charH, 
            font->charW, 
            font->charH
        );
    }
}
