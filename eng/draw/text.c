#include "text.h"

#include "type/vec.h"
#include "eng.h"
#include "draw/draw.h"

#include <string.h>
#include <stdio.h>

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


void cBDrawText2d(CBtexture* tex, char txt[], int fontSize, vec2 pos, CBalignment align){
    char* cft = loadEpicFile("data/eng/font.cft",  0);
    for (int i = 0; txt[i] != '\0'; i++) {
        //printf("%c\n", (cft["e"]));
        cbTex(tex, pos.x + i * 50, pos.y, 5 * 10, 8 * 10, (cft[txt[i]]) * 5,0, 5,8);
    }
}
