#include "input/input.h"
#include <eng.h>

void init(void) {}
void update(void) {}

void render(void) {
    cbFClear(.2f, .3f, .4f);

    if (cbIsMouseHeld(GLFW_MOUSE_BUTTON_LEFT))
        cbTint(255,0,0);
    else 
        cbTint(0,255,0);

    if (cbIsKeyHeld(GLFW_KEY_SPACE))
        cbRect(CB_WIDTH-cbMouseX,CB_HEIGHT-cbMouseY, 512,512);
    else
        cbRect(cbMouseX,cbMouseY, 128,128);
}

void clean(void) {}

int main(void) {
    return cbMain(
        "input",
        800,600,
        init,
        update,
        render,
        clean
        );
}

