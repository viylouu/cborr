#include <GL/gl.h>

void IMPL_cbClear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

