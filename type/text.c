#include "text.h"

#include "type/tex.h"
#include "type/vec.h"
#include "eng.h"
#include "draw/draw.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

CBfont* cbLoadFont(const char* file) {
    CBfont* fnt = malloc(sizeof(CBfont));
    fnt->atlas = cbLoadTexture(file);
    fnt->charW = fnt->atlas->width/256;
    fnt->charH = fnt->atlas->height/256;

    return fnt;
}

void cbUnloadFont(CBfont* font) {
    free(font);
}

void cbText(CBfont* font, const char* text, int fontSize, float x, float y) {
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
