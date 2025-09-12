#include <eng.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


vec2 pos1 = {0,0};
vec2 pos2 = {5,9};


CBfont* font;

void init(void) {
    font = cbLoadFont("data/eng/font.png", 5,8);
}

void update(void) { }

void render(void) {
    cbFClear(.2f, .3f, .4f);

    cbTint(255,0,0);
    //cbTex(tex, 0,0,CB_WIDTH,CB_HEIGHT);
    cbDrawText(font, "epic gamer!!!!!", 12, 0,0);
}

void clean(void) {
    cbUnloadFont(font);
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

