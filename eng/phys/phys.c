#include "phys.h"
#include <stdbool.h>
#include <math.h>

const float GRAV = 9.81;
//maybe change return type idk tho
unsigned char cbCheckRectColl(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2){
    return (x1 + w1 >= x2 && x1 <= x2 + w2 &&
            y1 <= y2 + h2 && y1 + h1 >= y2);
}

float cbCheckDistance(float x1, float y1, float  x2, float y2) {
    return sqrtf(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}