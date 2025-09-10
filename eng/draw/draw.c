#include "draw.h"
#include "mat/mat.h"
#include "shader/shader.h"
#include "tex/tex.h"

#include <glad/glad.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "dyn/dyn.h"
#include <string.h>

#define nil NULL

struct {
    struct {
        uint32_t vao;
        uint32_t bo;
        uint32_t tbo;
        uint32_t prog;
        int32_t loc_insts;
        int32_t loc_proj;
    } rect;

    struct {
        uint32_t vao;
        uint32_t bo;
        uint32_t tbo;
        uint32_t prog;
        int32_t loc_insts;
        int32_t loc_proj;
        int32_t loc_tex;
    } tex;
} bufs;

typedef enum {
    CB_RECT,
    CB_TEXTURE
} BatchType;

#pragma pack(4)
typedef struct {
    mat4 trans;
    float x;
    float y;
    float w;
    float h;
    float sx;
    float sy;
    float sw;
    float sh;
    float r;
    float g;
    float b;
    float a;
} InstanceData;
#pragma pack()

struct {
    BatchType type;
    CBtexture* tex;
    dyn data;
    bool wasUsed;
} batch;

mat4 proj3d;
mat4 proj2d;
mat4 trans;

const int maxBatchSize = 65536;
int maxBufferSize;

float fr;
float fg;
float fb;
float fa;

float fov = 90;

void cbDrawSetup(void) {
    cbDynArrInit(&batch.data, sizeof(InstanceData));

    // waaah
    if (sizeof(InstanceData) != 112) { exit(1); }

    maxBufferSize = maxBatchSize * sizeof(InstanceData);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bufs.rect.prog = cbLoadProgram("data/eng/rect.vert", "data/eng/rect.frag");
    glGenVertexArrays(1, &bufs.rect.vao);

    bufs.rect.loc_insts = glGetUniformLocation(bufs.rect.prog, "insts");
    bufs.rect.loc_proj = glGetUniformLocation(bufs.rect.prog, "proj");
    
    glGenBuffers(1, &bufs.rect.bo);
    glBindBuffer(GL_TEXTURE_BUFFER, bufs.rect.bo);
    glBufferData(GL_TEXTURE_BUFFER, maxBufferSize, nil, GL_DYNAMIC_DRAW);

    glGenTextures(1, &bufs.rect.tbo);
    glBindTexture(GL_TEXTURE_BUFFER, bufs.rect.tbo);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, bufs.rect.bo);

    bufs.tex.prog = cbLoadProgram("data/eng/tex.vert", "data/eng/tex.frag");
    glGenVertexArrays(1, &bufs.tex.vao);

    bufs.tex.loc_insts = glGetUniformLocation(bufs.tex.prog, "insts");
    bufs.tex.loc_proj = glGetUniformLocation(bufs.tex.prog, "proj");
    bufs.tex.loc_tex = glGetUniformLocation(bufs.tex.prog, "tex");

    glGenBuffers(1, &bufs.tex.bo);
    glBindBuffer(GL_TEXTURE_BUFFER, bufs.tex.bo);
    glBufferData(GL_TEXTURE_BUFFER, maxBufferSize, nil, GL_DYNAMIC_DRAW);

    glGenTextures(1, &bufs.tex.tbo);
    glBindTexture(GL_TEXTURE_BUFFER, bufs.tex.tbo);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, bufs.tex.bo);
}

void cbDrawUpdate(int width, int height) {
    if (fov < 179) {
        const float aspect = (float)width / (float)height;
        const float torad = 3.1415925635897932384626f / 180.f;
        const float fovy = fov * torad;

        const float far = 10000;
        const float near = .1f;
        const float range = far - near;

        cbMatMake(&proj3d,
            1/(aspect*tanf(fovy/2.f)), 0, 0, 0,
            0, -1/tanf(fovy/2.f), 0, 0,
            0, 0, -(far + near) / range, -(2 * far * near) / range,
            0, 0, 0, 0
            );
    }

    cbMatOrtho(&proj2d, 0,width,height,0, -1,1);
}

void cbDrawClean(void) {
    cbDynArrFree(&batch.data);

    glDeleteVertexArrays(1, &bufs.tex.vao);
    glDeleteBuffers(1, &bufs.tex.tbo);
    glDeleteBuffers(1, &bufs.tex.bo);
    glDeleteProgram(bufs.tex.prog);

    glDeleteVertexArrays(1, &bufs.rect.vao);
    glDeleteBuffers(1, &bufs.rect.tbo);
    glDeleteBuffers(1, &bufs.rect.bo);
    glDeleteProgram(bufs.rect.prog);
}


void cbDrawFlush(void) {
    if (batch.data.size == 0) return;

    switch (batch.type) {
        case CB_RECT:
            glUseProgram(bufs.rect.prog);
            glBindVertexArray(bufs.rect.vao);

            glUniformMatrix4fv(bufs.rect.loc_proj, 1,0, proj2d);

            glBindBuffer(GL_TEXTURE_BUFFER, bufs.rect.bo);
            glBufferSubData(GL_TEXTURE_BUFFER, 0, batch.data.size * sizeof(InstanceData), batch.data.data);

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_BUFFER, bufs.rect.tbo);
            glUniform1i(bufs.rect.loc_insts, 1);

            glDrawArraysInstanced(GL_TRIANGLES, 0, 6, batch.data.size);

            glBindTexture(GL_TEXTURE_BUFFER, 0);
            glBindBuffer(GL_TEXTURE_BUFFER, 0);
            glBindVertexArray(0);
            glUseProgram(0);

            break;
        case CB_TEXTURE:
            if (!batch.tex) { printf("texture is null!\n"); return; }

            glUseProgram(bufs.tex.prog);
            glBindVertexArray(bufs.tex.vao);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, batch.tex->id);
            glUniform1i(bufs.tex.loc_tex, 0);

            glUniformMatrix4fv(bufs.tex.loc_proj, 1,0, proj2d);

            glBindBuffer(GL_TEXTURE_BUFFER, bufs.tex.bo);
            glBufferSubData(GL_TEXTURE_BUFFER, 0, batch.data.size * sizeof(InstanceData), batch.data.data);

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_BUFFER, bufs.tex.tbo);
            glUniform1i(bufs.tex.loc_insts, 1);

            glDrawArraysInstanced(GL_TRIANGLES, 0, 6, batch.data.size);

            glBindTexture(GL_TEXTURE_BUFFER, 0);
            glBindBuffer(GL_TEXTURE_BUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindVertexArray(0);
            glUseProgram(0);

            break;
    }

    cbDynArrClear(&batch.data);
}


void cbResetTransform(void) {
    cbMatIdentity(&trans);
}


void IMPL_cbTranslate(float x, float y, float z) {
    mat4 temp;
    cbMatTranslate(&temp, x,y,z);
    cbMatMultiply(&trans, trans, temp);
}

void IMPL_cbScale(float x, float y, float z) {
    mat4 temp;
    cbMatScale(&temp, x,y,z);
    cbMatMultiply(&trans, trans, temp);
}

void IMPL_cbRotate(float x, float y, float z) {
    mat4 rx, ry, rz;
    cbMatRotateX(&rx, x);
    cbMatRotateY(&ry, y);
    cbMatRotateZ(&rz, z);

    mat4 temp;
    cbMatMultiply(&temp, ry, rx);
    cbMatMultiply(&temp, rz, temp);
    cbMatMultiply(&trans, trans, temp);
}


void IMPL_cbTint(float r, float g, float b, float a) { fr = r; fg = g; fb = b; fa = a; }

void IMPL_cbClear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void IMPL_cbRect(float x, float y, float w, float h) {
    if (batch.wasUsed) {
        if (batch.type != CB_RECT) cbDrawFlush();
        if (batch.data.size >= maxBatchSize) cbDrawFlush();
    } else batch.wasUsed = true;

    InstanceData data;
    memcpy(data.trans, trans, sizeof(trans));
    data.x = x;
    data.y = y;
    data.w = w;
    data.h = h;
    data.r = fr;
    data.g = fg;
    data.b = fb;
    data.a = fa;

    batch.type = CB_RECT;
    batch.tex = nil;
    cbDynArrPushBack(&batch.data, &data);

    /*glUseProgram(bufs.rect.prog);
    glBindVertexArray(bufs.rect.vao);

    glUniformMatrix4fv(bufs.rect.loc_proj, 1,0, proj2d);
    glUniformMatrix4fv(bufs.rect.loc_trans, 1,0, trans);
    glUniform2f(bufs.rect.loc_pos, x,y);
    glUniform2f(bufs.rect.loc_size, w,h);
    glUniform4f(bufs.rect.loc_col, fr,fg,fb,fa);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glUseProgram(0);*/
}

void IMPL_cbTex(CBtexture* tex, float x, float y, float w, float h, float sx, float sy, float sw, float sh) {
    if (batch.wasUsed) {
        if (batch.type != CB_TEXTURE) cbDrawFlush();
        if (batch.data.size >= maxBatchSize) cbDrawFlush();
        if (batch.tex != tex) { cbDrawFlush(); batch.tex = tex; }
    } else batch.wasUsed = true;

    if (!tex) { printf("texture is nil!"); return; }

    InstanceData data;
    memcpy(data.trans, trans, sizeof(trans));
    data.x = x;
    data.y = y;
    data.w = w;
    data.h = h;
    data.sx = sx / tex->width;
    data.sy = sy / tex->height;
    data.sw = sw / tex->width;
    data.sh = sh / tex->height;
    data.r = fr;
    data.g = fg;
    data.b = fb;
    data.a = fa;

    batch.type = CB_TEXTURE;
    batch.tex = tex;
    cbDynArrPushBack(&batch.data, &data);

    /*if (!tex) { printf("texture is null!\n"); return; }

    glUseProgram(bufs.tex.prog);
    glBindVertexArray(bufs.tex.vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex->id);
    glUniform1i(bufs.tex.loc_tex, 0);

    glUniformMatrix4fv(bufs.tex.loc_proj, 1,0, proj2d);
    glUniformMatrix4fv(bufs.tex.loc_trans, 1,0, trans);
    glUniform2f(bufs.tex.loc_pos, x,y);
    glUniform2f(bufs.tex.loc_size, w,h);
    glUniform2f(bufs.tex.loc_samp_pos, sx/(float)tex->width,sy/(float)tex->height);
    glUniform2f(bufs.tex.loc_samp_size, sw/(float)tex->width,sh/(float)tex->height);
    glUniform4f(bufs.tex.loc_tint, fr,fg,fb,fa);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);*/
}
