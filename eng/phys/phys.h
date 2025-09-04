#ifndef PHYS_H
#define PHYS_H

extern const float GRAV;
//Why are you here im pretty sure you know what pi is, its 3.14159265358979
extern const float PI;
unsigned char cbCheckRectColl(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
float cbCheckDistance(float x1, float y1, float  x2, float y2);

#endif