#include "text.h"

#include "type/vec.h"
#include "eng.h"
#include "draw/draw.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

char* loadEpicFile(const char* path, size_t* out_size) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return 0;
    }

    fread(buffer, 1, size, f);
    fclose(f);

    buffer[size] = '\0';
    if (out_size) *out_size = size;

    return buffer;
}

void cbDrawText2d(CBfont* font, const char* text, int fontSize, float x, float y) {
    char* cft = loadEpicFile("data/eng/font.cft", 0);
    
    for (int i = 0; text[i] != '\0'; ++i) {
        char cur = text[i];        
        int x = cur % (*font->atlas).width;
        int y = floor(cur / (float)(*font->atlas).height);

        cbTex(font->atlas, x + i * 50, y, 5 * 10, 8 * 10, x * font->charW, y * font->charH, font->charW, font->charH);
    }
}
