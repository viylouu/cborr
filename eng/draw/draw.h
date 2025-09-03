#ifndef DRAW_H
#define DRAW_H

#include "tex/tex.h"

void cbDrawSetup(void);
void cbDrawUpdate(int width, int height);
void cbDrawClean(void);

// ------- funcs
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
#define SELECT_FCLEAR(...) CAT(fclear_, VA_NARGS(__VA_ARGS__))
#define cbFClear(...) SELECT_FCLEAR(__VA_ARGS__)(__VA_ARGS__)
#define fclear_1(r) IMPL_cbClear(r,r,r,1.f)
#define fclear_3(r,g,b) IMPL_cbClear(r,g,b,1.f)
#define fclear_4(r,g,b,a) IMPL_cbClear(r,g,b,a)

#define SELECT_CLEAR(...) CAT(clear_, VA_NARGS(__VA_ARGS__))
#define cbClear(...) SELECT_CLEAR(__VA_ARGS__)(__VA_ARGS__)
#define clear_1(r) IMPL_cbClear(r/255.f,r/255.f,r/255.f,1.f)
#define clear_3(r,g,b) IMPL_cbClear(r/255.f,g/255.f,b/255.f,1.f)
#define clear_4(r,g,b,a) IMPL_cbClear(r/255.f,g/255.f,b/255.f,a/255.f)

#define SELECT_FTINT(...) CAT(ftint_, VA_NARGS(__VA_ARGS__))
#define cbFTint(...) SELECT_FTINT(__VA_ARGS__)(__VA_ARGS__)
#define ftint_1(r) IMPL_cbTint(r,r,r,1.f)
#define ftint_3(r,g,b) IMPL_cbTint(r,g,b,1.f)
#define ftint_4(r,g,b,a) IMPL_cbTint(r,g,b,a)

#define SELECT_TINT(...) CAT(tint_, VA_NARGS(__VA_ARGS__))
#define cbTint(...) SELECT_TINT(__VA_ARGS__)(__VA_ARGS__)
#define tint_1(r) IMPL_cbTint(r/255.f,r/255.f,r/255.f,1.f)
#define tint_3(r,g,b) IMPL_cbTint(r/255.f,g/255.f,b/255.f,1.f)
#define tint_4(r,g,b,a) IMPL_cbTint(r/255.f,g/255.f,b/255.f,a/255.f)

#define cbFRect(x,y,w,h) IMPL_cbRect(x,y,w,h)
#define cbRect(x,y,w,h) IMPL_cbRect(x,y,w,h)

#define SELECT_FTEX(...) CAT(ftex_, VA_NARGS(__VA_ARGS__))
#define cbFTex(...) SELECT_FTEX(__VA_ARGS__)(__VA_ARGS__)
#define ftex_3(tex,x,y) IMPL_cbTex(tex,x,y,(*tex).width,(*tex).height,0,0,(*tex).width,(*tex).height)
#define ftex_5(tex,x,y,w,h) IMPL_cbTex(tex,x,y,w,h,0,0,(*tex).width,(*tex).height)
#define ftex_7(tex,x,y,sx,sy,sw,sh) IMPL_cbTex(tex,x,y,sw,sh,sx,sy,sw,sh)
#define ftex_9(tex,x,y,w,h,sx,sy,sw,sh) IMPL_cbTex(tex,x,y,w,h,sx,sy,sw,sh)

#define cbTex(...) cbFTex(__VA_ARGS__)

#endif
