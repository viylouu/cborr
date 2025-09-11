#include "phys.h"
#include "type/vec.h"

#include <stdint.h>
#include <math.h>

const float GRAV = 9.81;
//we prolly should make pi in our own math file
const float PI = 3.14159;
//oiler, haha funny
extern const float e = 2.71828;

uint8_t cbCheckRectColl(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2){
    return (x1 + w1 >= x2 && x1 <= x2 + w2 &&
            y1 <= y2 + h2 && y1 + h1 >= y2);
}

float cbCheckDistance2d(vec2 s1, vec2 s2) {
    return sqrtf(((s2.x - s1.x) * (s2.x - s1.x)) + ((s2.y - s1.y) * (s2.y - s1.y)));
}

float cbCheckDistance3d(float x1, float y1, float z1, float  x2, float y2, float z2){
    return sqrtf(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) + ((z2 - z1) * (z2 - z1)));
}


