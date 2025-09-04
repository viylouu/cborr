#include "mat.h"

#include <string.h>
#include <math.h>

void cbMatMake(
    mat4* mat,
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
) {
    float tmp[16] = {
        m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33
    };
    memcpy(*mat, tmp, sizeof(tmp));
}

void cbMatIdentity(mat4* mat) {
    cbMatMake(mat, 
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        );
}

void cbMatMultiply(mat4* out, const mat4 a, const mat4 b) {
    float result[16];

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result[row*4 + col] =
                a[row*4 + 0] * b[0*4 + col] +
                a[row*4 + 1] * b[1*4 + col] +
                a[row*4 + 2] * b[2*4 + col] +
                a[row*4 + 3] * b[3*4 + col];
        }
    }

    memcpy(*out, result, sizeof(result));
}

void cbMatOrtho(
    mat4* mat, 
    float left, float right,
    float bottom, float top,
    float near, float far
) {
    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    cbMatMake(mat, 
        2/rl, 0, 0, 0,
        0, 2/tb, 0, 0,
        0, 0,-2/fn, 0,
        -(right+left) / rl, -(top+bottom) / tb, -(far+near) / fn, 1
        );
}

void cbMatTranslate(
    mat4* mat,
    float x, float y, float z
) {
    cbMatMake(mat,
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
        );
}

void cbMatScale(
    mat4* mat,
    float x, float y, float z
) {
    cbMatMake(mat,
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
        );
}

void cbMatRotateX(mat4* mat, float ang) {
    float c = cosf(ang);
    float s = sinf(ang);

    cbMatMake(mat,
        1, 0, 0, 0,
        0, c,-s, 0,
        0, s, c, 0,
        0, 0, 0, 1
        );
}

void cbMatRotateY(mat4* mat, float ang) {
    float c = cosf(ang);
    float s = sinf(ang);

    cbMatMake(mat,
        c, 0, s, 0,
        0, 1, 0, 0,
       -s, 0, c, 0,
        0, 0, 0, 1
        );
}

void cbMatRotateZ(mat4* mat, float ang) {
    float c = cosf(ang);
    float s = sinf(ang);

    cbMatMake(mat,
        c,-s, 0, 0,
        s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        );
}
