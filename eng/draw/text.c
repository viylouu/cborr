#include "text.h"

#include "type/vec.h"
#include "eng.h"
#include "draw/draw.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

void cbDrawText2d(CBfont* font, const char* text, int fontSize, float x, float y) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char cur = text[i];        
        int x = cur % (*font->atlas).width;
        int y = floor(cur / (float)(*font->atlas).height);

        cbTex(
            font->atlas, 
            x + i * font->charW * fontSize, 
            y, 
            font->charW * fontSize, 
            font->charH * fontSize, 
            x * font->charW, 
            y * font->charH, 
            font->charW, 
            font->charH
        );
    }
}
