#include <eng.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


vec2 pos1 = {0,0};
vec2 pos2 = {5,9};


CBtexture* tex;
char* cft;

char* loadFuckYouFile(const char* path, size_t* out_size) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return 0;
    }

    fread(buffer, 1, size, f);
    fclose(f);

    buffer[size] = '\0';
    if (out_size) *out_size = size;

    return buffer;
}

void init(void) {
    tex = cbLoadTexture("data/eng/font.png");
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

