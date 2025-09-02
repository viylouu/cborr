#include "mat.h"
#include <string.h>

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

void cbMatOrtho(mat4* mat, 
                float left, float right,
                float bottom, float top,
                float near, float far) {
    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    cbMatMake(mat, 
        2/rl, 0,0,0,
        0, 2/tb, 0,0,
        0,0, -2/fn, 0,
        -(right+left) / rl,
        -(top+bottom) / tb,
        -(far+near) / fn,
        1
        );
}
