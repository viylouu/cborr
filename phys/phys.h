#ifndef PHYS_H
#define PHYS_H

#include "../type/vec.h"

extern const float GRAV;
//Why are you here im pretty sure you know what pi is, its 3.14159
extern const float PI;
//oiler, haha funny
extern const float e;
unsigned char cbCheckRectColl(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
unsigned char cbCheckPointRectColl(float x1, float y1, float x2, float y2, float w2, float h2);
float cbCheckDistance2d(vec2 s1, vec2 s2);
float cbCheckDistance3d(float x1, float y1, float z1, float  x2, float y2, float z2);

#endif
