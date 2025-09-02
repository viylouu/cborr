#include <eng.h>
#include <GLFW/glfw3.h>

void init(void) {}
void update(void) { }

void render(void) {
    cbFClear(.2f, .3f, .4f);
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
