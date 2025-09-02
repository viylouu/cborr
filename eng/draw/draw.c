#include "draw.h"
#include "mat/mat.h"

#include <GL/gl.h>
#include <stdint.h>

struct {
    struct {
        uint32_t vao;
        uint32_t prog;
        int32_t  loc_pos;
        int32_t  loc_size;
        int32_t  loc_col;
        int32_t  loc_proj;
    } rect;
} bufs;

mat4 proj;

void cbDrawSetup(int width, int height) {
    cbMatOrtho(&proj, 0,width,height,0, -1000,1000);
}


void IMPL_cbClear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void IMPL_cbRect(float x, float y, float w, float h, float r, float g, float b, float a) {
    
}
