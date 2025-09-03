#include "draw.h"
#include "mat/mat.h"
#include "shader/shader.h"

#include <glad/glad.h>
#include <stdint.h>
#include <stdio.h>

struct {
    struct {
        uint32_t vao;
        uint32_t prog;
        int32_t  loc_pos;
        int32_t  loc_size;
        int32_t  loc_col;
        int32_t  loc_proj;
    } rect;

    struct {
        uint32_t vao;
        uint32_t prog;
        int32_t  loc_pos;
        int32_t  loc_size;
        int32_t  loc_samp_pos;
        int32_t  loc_samp_size;
        int32_t  loc_tint;
        int32_t  loc_proj;
        int32_t  loc_tex;
    } tex;
} bufs;

mat4 proj;

float fr;
float fg;
float fb;
float fa;

void cbDrawSetup(void) {
    bufs.rect.prog = cbLoadProgram("data/eng/rect.vert", "data/eng/rect.frag");
    glGenVertexArrays(1, &bufs.rect.vao);

    bufs.rect.loc_pos  = glGetUniformLocation(bufs.rect.prog, "pos");
    bufs.rect.loc_size = glGetUniformLocation(bufs.rect.prog, "size");
    bufs.rect.loc_col  = glGetUniformLocation(bufs.rect.prog, "col");
    bufs.rect.loc_proj = glGetUniformLocation(bufs.rect.prog, "proj");

    bufs.tex.prog = cbLoadProgram("data/eng/tex.vert", "data/eng/tex.frag");
    glGenVertexArrays(1, &bufs.tex.vao);

    bufs.tex.loc_pos  = glGetUniformLocation(bufs.tex.prog, "pos");
    bufs.tex.loc_size = glGetUniformLocation(bufs.tex.prog, "size");
    bufs.tex.loc_samp_pos  = glGetUniformLocation(bufs.tex.prog, "samp_pos");
    bufs.tex.loc_samp_size = glGetUniformLocation(bufs.tex.prog, "samp_size");
    bufs.tex.loc_tint = glGetUniformLocation(bufs.tex.prog, "tint");
    bufs.tex.loc_proj = glGetUniformLocation(bufs.tex.prog, "proj");
    bufs.tex.loc_tex  = glGetUniformLocation(bufs.tex.prog, "tex");
}

void cbDrawUpdate(int width, int height) {
    cbMatOrtho(&proj, 0,width,height,0, -1000,1000);
}

void cbDrawClean(void) {
    glDeleteVertexArrays(1, &bufs.tex.vao);
    glDeleteProgram(bufs.tex.prog);

    glDeleteVertexArrays(1, &bufs.rect.vao);
    glDeleteProgram(bufs.rect.prog);
}


void IMPL_cbTint(float r, float g, float b, float a) { fr = r; fg = g; fb = b; fa = a; }

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

void IMPL_cbTex(CBtexture* tex, float x, float y, float w, float h, float sx, float sy, float sw, float sh) {
    if (!tex) { printf("texture is null!\n"); return; }

    glUseProgram(bufs.tex.prog);
    glBindVertexArray(bufs.tex.vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex->id);
    glUniform1i(bufs.tex.loc_tex, 0);

    glUniformMatrix4fv(bufs.tex.loc_proj, 1,0, proj);
    glUniform2f(bufs.tex.loc_pos, x,y);
    glUniform2f(bufs.tex.loc_size, w,h);
    glUniform2f(bufs.tex.loc_samp_pos, sx/(float)tex->width,sy/(float)tex->height);
    glUniform2f(bufs.tex.loc_samp_size, sw/(float)tex->width,sh/(float)tex->height);
    glUniform4f(bufs.tex.loc_tint, fr,fg,fb,fa);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}
