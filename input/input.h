#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef enum {
    CB_RELEASED,
    CB_PRESSED,
    CB_HELD,
    CB_UNPRESSED
} CBinputState;

extern float cbMouseX;
extern float cbMouseY;

void cbPollInput(GLFWwindow* window);

CBinputState cbGetKeyState(int scancode);
CBinputState cbGetMouseState(int scancode);

int cbIsKeyHeld(int scancode);
int cbIsKeyPressed(int scancode);
int cbIsKeyReleased(int scancode);

int cbIsMouseHeld(int scancode);
int cbIsMousePressed(int scancode);
int cbIsMouseReleased(int scancode);

#endif
