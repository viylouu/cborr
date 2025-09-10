#ifndef MAT_H
#define MAT_H

typedef float mat4[16];

void cbMatMake(
    mat4* mat,
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
);

void cbMatMultiply(mat4* out, const mat4 a, const mat4 b);

void cbMatOrtho(
    mat4* mat, 
    float left, float right,
    float bottom, float top,
    float near, float far
);

void cbMatIdentity(mat4* mat);

void cbMatTranslate(mat4* mat, float x, float y, float z);
void cbMatScale(mat4* mat, float x, float y, float z);

void cbMatRotateX(mat4* mat, float ang);
void cbMatRotateY(mat4* mat, float ang);
void cbMatRotateZ(mat4* mat, float ang);

#endif
