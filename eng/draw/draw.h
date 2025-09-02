#ifndef DRAW_H
#define DRAW_H

void cbDrawSetup(void);
void cbDrawUpdate(int width, int height);
void cbDrawClean(void);

// ------- funcs
void IMPL_cbFill(float r, float g, float b, float a);
void IMPL_cbClear(float r, float g, float b, float a);
void IMPL_cbRect(float x, float y, float w, float h);

// ------- function overload helpers
#define VA_NARGS_IMPL(_1,_2,_3,_4,N,...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__,4,3,2,1,0)

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

#define SELECT_FFILL(...) CAT(ffill_, VA_NARGS(__VA_ARGS__))
#define cbFFill(...) SELECT_FFILL(__VA_ARGS__)(__VA_ARGS__)
#define ffill_1(r) IMPL_cbFill(r,r,r,1.f)
#define ffill_3(r,g,b) IMPL_cbFill(r,g,b,1.f)
#define ffill_4(r,g,b,a) IMPL_cbFill(r,g,b,a)

#define SELECT_FILL(...) CAT(fill_, VA_NARGS(__VA_ARGS__))
#define cbFill(...) SELECT_FILL(__VA_ARGS__)(__VA_ARGS__)
#define fill_1(r) IMPL_cbFill(r/255.f,r/255.f,r/255.f,1.f)
#define fill_3(r,g,b) IMPL_cbFill(r/255.f,g/255.f,b/255.f,1.f)
#define fill_4(r,g,b,a) IMPL_cbFill(r/255.f,g/255.f,b/255.f,a/255.f)

#define cbFRect(x,y,w,h) IMPL_cbRect(x,y,w,h)
#define cbRect(x,y,w,h) IMPL_cbRect(x,y,w,h)

#endif
