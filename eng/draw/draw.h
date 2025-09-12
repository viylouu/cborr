#ifndef DRAW_H
#define DRAW_H

//// ENGINE USED
//
// cbDrawSetup(void)
//  sets up draw.h
//
// cbDrawUpdate(int width, int height)
//  updates draw.h using width and height
//
// cbDrawClean(void)
//  un sets up draw.h
//  the cleanup
//
//// USER USED (NO OVERLOADS)
//
// cbResetTransform(void)
//  resets the transformation matrix
//  this gets called at the start of each frame
//
// cbDrawFlush(void)
//  forces the gpu to start rendering the current batch
//  this gets called at the end of each frame
//  this also gets called when swapping buffer types
//  and also in some specific cases (see draw.c IMPL_name)
//
//// USER USED (OVERLOADS)
//
/// MATRICES
//
// cbTranslate
//      ( float x, float y, float z )
//      ( float x, float y)
//  applies a translation matrix
//
// cbScale
//      ( float x, float y, float z )
//      ( float x, float y )
//  applies a scale matrix
//
// cbRotate
//      ( float x, float y, float z )
//      ( float ang )
//  applies a rotation matrix
//
/// DRAW STATE
//
// cbFTint
//      ( float r, float g, float b, float a )
//      ( float r, float g, float b )
//      ( float val )
//  changes the current color tint value
//  this is only because of the limited overload system used
//  batch instances all have unique color values
//  color format is in [0,1]
//
// cbTint
//      ( float r, float g, float b, float a )
//      ( float r, float g, float b )
//      ( float val )
//  changes the current color tint value
//  this is only because of the limited overload systme used
//  batch instances all have unique color values
//  color format is in [0,255]
//
/// DRAW MISC
//
// cbFClear
//      ( float r, float g, float b, float a )
//      ( float r, float g, float b )
//      ( float val )
//  clears the screen using the desired color
//  color format is in [0,1]
//
// cbClear
//      ( float r, float g, float b, float a )
//      ( float r, float g, float b )
//      ( float val )
//  clears the screen using the desired color
//  color format is in [0,255]
//
/// 2D DRAW ACTUAL STUFF OMG SO LOW
//
// INFO:
//  stuff here is drawn in pixel space coordinates UNLESS stated otherwise
//  origin is at the top left UNLESS stated otherwise
//
// cbRect
//      ( float x, float y, float w, float h )
//  draws a rectangle using the given values
//
// cbTex
//      ( CBtexture* tex, float x, float y, float w, float h, float sx, float sy, float sw, float sh )
//      ( CBtexture* tex, float x, float y, float sx, float sy, float sw, float sh )
//      ( CBtexture* tex, float x, float y, float w, float h )
//      ( CBtexture* tex, float x, float y )
//  draws a texture using the given values
//  the s(x/y/w/h) denotes a sample coordinate
//  sample origin is top left
//  sample is in pixel space coordinates
//
//



extern float fov;
extern const int maxBatchSize;

void cbDrawSetup(void);
void cbDrawUpdate(int width, int height);
void cbDrawClean(void);
void cbResetTransform(void);
void cbDrawFlush(void);

// ------- funcs
void IMPL_cbTranslate(float x, float y, float z);
void IMPL_cbScale(float x, float y, float z);
void IMPL_cbRotate(float x, float y, float z);

void IMPL_cbTint(float r, float g, float b, float a);
void IMPL_cbClear(float r, float g, float b, float a);
void IMPL_cbRect(float x, float y, float w, float h);
void IMPL_cbTex(CBtexture* tex, float x, float y, float w, float h, float sx, float sy, float sw, float sh);

// ------- function overload helpers
#define VA_NARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__,9,8,7,6,5,4,3,2,1,0)

#define CAT2(a,b) a##b
#define CAT(a,b) CAT2(a,b)

// ------- function overloads
#define SELECT_TRANSLATE(...) CAT(translate_, VA_NARGS(__VA_ARGS__))
#define cbTranslate(...) SELECT_TRANSLATE(__VA_ARGS__)(__VA_ARGS__)
#define translate_2(x,y) IMPL_cbTranslate(x,y,0)
#define translate_3(x,y,z) IMPL_cbTranslate(x,y,z)

#define SELECT_SCALE(...) CAT(scale_, VA_NARGS(__VA_ARGS__))
#define cbScale(...) SELECT_SCALE(__VA_ARGS__)(__VA_ARGS__)
#define scale_2(x,y) IMPL_cbScale(x,y,0)
#define scale_3(x,y,z) IMPL_cbScale(x,y,z)

#define SELECT_ROTATE(...) CAT(rotate_, VA_NARGS(__VA_ARGS__))
#define cbRotate(...) SELECT_ROTATE(__VA_ARGS__)(__VA_ARGS__)
#define rotate_1(ang) IMPL_cbRotate(0,0,ang)
#define rotate_3(x,y,z) IMPL_cbRotate(x,y,z)

#define SELECT_FCLEAR(...) CAT(fclear_, VA_NARGS(__VA_ARGS__))
#define cbFClear(...) SELECT_FCLEAR(__VA_ARGS__)(__VA_ARGS__)
#define fclear_1(r) IMPL_cbClear(r,r,r,1.f)
#define fclear_3(r,g,b) IMPL_cbClear(r,g,b,1.f)
#define fclear_4(r,g,b,a) IMPL_cbClear(r,g,b,a)
git 
#define SELECT_CLEAR(...) CAT(clear_, Vgit A_NARGS(__VA_ARGS__))
#define cbClear(...) SELECT_CLEAR(__VA_git ARGS__)(__VA_ARGS__)
#define clear_1(r) IMPL_cbClear(r/255.fgit ,r/255.f,r/255.f,1.f)
#define clear_3(r,g,b) IMPL_cbClear(r/255.f,g/255.f,b/255.f,1.f)
#define clear_4(r,g,b,a) IMPL_cbClear(r/255.f,g/255.f,b/255.f,a/255.f)

#define SELECT_FTINT(...) CAT(ftint_, VA_NARGS(__VA_ARGS__))
#define cbFTint(...) SELECT_FTINT(__VA_ARGS__)(__VA_ARGS__)
#define ftint_1(val) IMPL_cbTint(val,val,val,1.f)
#define ftint_3(r,g,b) IMPL_cbTint(r,g,b,1.f)
#define ftint_4(r,g,b,a) IMPL_cbTint(r,g,b,a)

#define SELECT_TINT(...) CAT(tint_, VA_NARGS(__VA_ARGS__))
#define cbTint(...) SELECT_TINT(__VA_ARGS__)(__VA_ARGS__)
#define tint_1(val) IMPL_cbTint(val/255.f,val/255.f,val/255.f,1.f)
#define tint_3(r,g,b) IMPL_cbTint(r/255.f,g/255.f,b/255.f,1.f)
#define tint_4(r,g,b,a) IMPL_cbTint(r/255.f,g/255.f,b/255.f,a/255.f)

#define SELECT_RECT(...) CAT(rect_, VA_NARGS(__VA_ARGS__))
#define cbRect(...) SELECT_RECT(__VA_ARGS__)(__VA_ARGS__)
#define rect_4(x,y,w,h) IMPL_cbRect(x,y,w,h)

#define SELECT_TEX(...) CAT(tex_, VA_NARGS(__VA_ARGS__))
#define cbTex(...) SELECT_TEX(__VA_ARGS__)(__VA_ARGS__)
#define tex_3(tex,x,y) IMPL_cbTex(tex,x,y,tex->width,tex->height,0,0,tex->width,tex->height)
#define tex_5(tex,x,y,w,h) IMPL_cbTex(tex,x,y,w,h,0,0,tex->width,tex->height)
#define tex_7(tex,x,y,sx,sy,sw,sh) IMPL_cbTex(tex,x,y,sw,sh,sx,sy,sw,sh)
#define tex_9(tex,x,y,w,h,sx,sy,sw,sh) IMPL_cbTex(tex,x,y,w,h,sx,sy,sw,sh)

#endif
