#include "text.h"
#include "../type/vec.h"
#include "draw.h"
#include "../eng.h"
#include <string.h>


void cBDrawText2d(CBtexture* tex, char txt[], int fontSize, vec2 pos, CBalignment align){
    int sizex = strlen(txt);
    float sizey = sizex / 10;

    cbTex(tex, pos.x, pos.y, CB_WIDTH, CB_HEIGHT);
}