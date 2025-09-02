#include <eng.h>

void init(void) {}
void update(void) {}

void render(void) {
    cbClear(255,255,255);
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
