#include <eng.h>

CBtexture* tex;

void init(void) {
    tex = cbLoadTexture("examples/texture/tex.png");
}

void update(void) { }

void render(void) {
    cbFClear(.2f, .3f, .4f);

    cbTint(255,0,0);
    cbTex(tex, 0,0,CB_WIDTH,CB_HEIGHT);
}

void clean(void) {
    cbUnloadTexture(tex);
}

int main(void) {
    return cbMain(
        "basic window!!!!",
        800,600,
        init,
        update,
        render,
        clean
        );
}
