#include "tex.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_THREAD_LOCALS
#include <stb/stbimage.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void cbUnloadTexture(CBtexture* tex) {
    glDeleteTextures(1, &(*tex).id);
    free(tex);
}

CBtexture* cbLoadFromData(uint8_t* data, size_t size) {
    int32_t w;
    int32_t h;
    int32_t c;
    uint8_t* texdata = stbi_load_from_memory(data, size, &w,&h,&c, 4);
    if (!texdata) { printf("failed to load texture!"); return 0; }

    uint32_t id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texdata);

    CBtexture* tex = malloc(sizeof(CBtexture));
    tex->id = id;
    tex->width = w;
    tex->height = h;
    tex->filter = CB_NEAREST;

    return tex;
}

char* loadFileData(const char* path, size_t* out_size) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long size_long = ftell(f);
    if (size_long < 0) { fclose(f); printf("file size was 0?\n"); return 0; }
    size_t size = (size_t)size_long;

    rewind(f);

    char* buffer = malloc(size);
    if (!buffer) {
        fclose(f);
        return 0;
    }

    fread(buffer, 1, size, f);
    fclose(f);

    *out_size = size;

    return buffer;
}

CBtexture* cbLoadTexture(const char* path) {
    size_t size;
    char* buf = loadFileData(path, &size);
    if (!buf) {
        printf("failed to read file at \"%s\"\n", path);
        return 0;
    }

    CBtexture* tex = cbLoadFromData((uint8_t*)buf, size);
    free(buf);

    if (!tex) return 0;

    return tex;
}
