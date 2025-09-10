#include "shad.h"

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t cbCompileProgram(uint32_t* shaders, uint32_t amount) {
    uint32_t prog = glCreateProgram();

    for (uint32_t i = 0; i < amount; ++i)
        glAttachShader(prog, shaders[i]);
    glLinkProgram(prog);

    int succ;
    glGetProgramiv(prog, GL_LINK_STATUS, &succ);
    if (!succ) {
        int len = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

        char* log = malloc(len);
        glGetProgramInfoLog(prog, len, 0, log);

        printf("program compile err!\n%s\n", log);
        free(log);

        glDeleteProgram(prog);
        return 0;
    }

    return prog;
}

uint32_t cbLoadShaderFromSrc(uint32_t type, const char** src) {
    uint32_t shad = glCreateShader(type);
    glShaderSource(shad, 1, src, 0);
    glCompileShader(shad);

    int succ = 0;
    glGetShaderiv(shad, GL_COMPILE_STATUS, &succ);
    if (!succ) {
        int len = 0;
        glGetShaderiv(shad, GL_INFO_LOG_LENGTH, &len);

        char* log = malloc(len);
        glGetShaderInfoLog(shad, len, 0, log);

        printf("shader compile err!\n%s\n", log);
        free(log);

        glDeleteShader(shad);
        return 0;
    }

    return shad;
}

uint32_t cbLoadProgramFromSrc(const char** vertSource, const char** fragSource) {
    uint32_t vert = cbLoadShaderFromSrc(GL_VERTEX_SHADER, vertSource);
    uint32_t frag = cbLoadShaderFromSrc(GL_FRAGMENT_SHADER, fragSource);

    uint32_t shads[2] = { vert, frag };
    uint32_t prog = cbCompileProgram(shads, 2);

    glDeleteShader(vert);
    glDeleteShader(frag);

    return prog;
}

char* loadFile(const char* path, size_t* out_size) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return 0;
    }

    fread(buffer, 1, size, f);
    fclose(f);

    buffer[size] = '\0';
    if (out_size) *out_size = size;

    return buffer;
}

uint32_t cbLoadShader(uint32_t type, const char* path) {
    char* buf = loadFile(path, 0);
    if (!buf) {
        printf("failed to read shader at \"%s\"\n", path);
        return 0;
    }

    const char* src = buf;

    uint32_t shad = cbLoadShaderFromSrc(type, &src);

    free(buf);

    return shad;
}

uint32_t cbLoadProgram(const char* vertPath, const char* fragPath) {
    char* vBuf = loadFile(vertPath, 0);
    char* fBuf = loadFile(fragPath, 0);

    const char* vSrc = vBuf;
    const char* fSrc = fBuf;

    uint32_t prog = cbLoadProgramFromSrc(&vSrc, &fSrc);

    free(vBuf);
    free(fBuf);

    return prog;
}
