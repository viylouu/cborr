#ifndef TEX_H
#define TEX_H

typedef enum {
    CB_NEAREST,
    CB_BILINEAR
} CBfilter;

typedef struct {
    unsigned int id;
    int width;
    int height;
    CBfilter filter;
} CBtexture;


void cbUnloadTexture(CBtexture* tex);
CBtexture* cbLoadFromData(unsigned char* data, unsigned long size);
CBtexture* cbLoadTexture(const char* path);

#endif
