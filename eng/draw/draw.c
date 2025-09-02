#include "draw.h"
#include "mat/mat.h"
#include "shader/shader.h"

#include <glad/glad.h>
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

float fr;
float fg;
float fb;
float fa;

void cbDrawSetup(void) {
    bufs.rect.prog = loadProgram("data/eng/rect.vert", "data/eng/rect.frag");
    glGenVertexArrays(1, &bufs.rect.vao);

    bufs.rect.loc_pos  = glGetUniformLocation(bufs.rect.prog, "pos");
    bufs.rect.loc_size = glGetUniformLocation(bufs.rect.prog, "size");
    bufs.rect.loc_col  = glGetUniformLocation(bufs.rect.prog, "col");
    bufs.rect.loc_proj = glGetUniformLocation(bufs.rect.prog, "proj");
}

void cbDrawUpdate(int width, int height) {
    cbMatOrtho(&proj, 0,width,height,0, -1000,1000);
}

void cbDrawClean(void) {
    glDeleteVertexArrays(1, &bufs.rect.vao);
    glDeleteProgram(bufs.rect.prog);
}


void IMPL_cbFill(float r, float g, float b, float a) { fr = r; fg = g; fb = b; fa = a; }

void IMPL_cbClear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void IMPL_cbRect(float x, float y, float w, float h) {
    glUseProgram(bufs.rect.prog);
    glBindVertexArray(bufs.rect.vao);

    glUniformMatrix4fv(bufs.rect.loc_proj, 1,0, proj);
    glUniform2f(bufs.rect.loc_pos, x,y);
    glUniform2f(bufs.rect.loc_size, w,h);
    glUniform4f(bufs.rect.loc_col, fr,fg,fb,fa);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glUseProgram(0);
}
