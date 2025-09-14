#ifndef TEX_H
#define TEX_H

#include <stdlib.h>

typedef enum {
    CB_NEAREST,
    CB_BILINEAR
} CBfilter;

typedef struct {
    unsigned int id;
    unsigned int fbo;
    int width;
    int height;
    CBfilter filter;
} CBtexture;


void cbUnloadTexture(CBtexture* tex);
CBtexture* cbCreateTexture(int width, int height);
CBtexture* cbLoadFromData(unsigned char* data, size_t size);
CBtexture* cbLoadTexture(const char* path);

#endif
