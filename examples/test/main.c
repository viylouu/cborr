#include <eng.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


vec2 pos1 = {0,0};
vec2 pos2 = {5,9};


CBtexture* tex;

void init(void) {
    tex = cbLoadTexture("examples/texture/tex.png");
}

void update(void) { }

void render(void) {
    cbFClear(.2f, .3f, .4f);

    cbTint(255,0,0);
    //cbTex(tex, 0,0,CB_WIDTH,CB_HEIGHT);
    cBDrawText2d(tex,"epic", 12, pos1, CB_LEFT);
}

void clean(void) {
    cbUnloadTexture(tex);
}


int main(){
    return cbMain(
        "basic window!!!!",
        800,600,
        init,
        update,
        render,
        clean
        );
    
}

