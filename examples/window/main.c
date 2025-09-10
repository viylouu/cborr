#include <eng.h>

void init(void) {}
void update(void) { }

void render(void) {
    cbFClear(.2f, .3f, .4f);

    cbTint(255,0,0);
    cbRect(0,0, 64,64);
}

void clean(void) {}

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
