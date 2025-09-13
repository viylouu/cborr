#include "input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

CBinputState keys[GLFW_KEY_LAST+1];
CBinputState mouse[GLFW_MOUSE_BUTTON_LAST+1];

float cbMouseX;
float cbMouseY;

void cbPollInput(GLFWwindow* window) {
    double BAD_x, BAD_y; // bad because double
    glfwGetCursorPos(window, &BAD_x, &BAD_y);
    cbMouseX = BAD_x;
    cbMouseY = BAD_y;

    for (int i = 0; i <= GLFW_KEY_LAST; ++i) {
        CBinputState prev = keys[i];
        keys[i] = (CBinputState)glfwGetKey(window, i);
        if (keys[i] == CB_RELEASED && ( prev == CB_RELEASED || prev == CB_UNPRESSED )) keys[i] = CB_UNPRESSED;
        if (keys[i] == CB_PRESSED && ( prev == CB_PRESSED || prev == CB_HELD )) keys[i] = CB_HELD;
    }

    for (int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i) {
        CBinputState prev = mouse[i];
        mouse[i] = (CBinputState)glfwGetMouseButton(window, i);
        if (mouse[i] == CB_RELEASED && ( prev == CB_RELEASED || prev == CB_UNPRESSED )) mouse[i] = CB_UNPRESSED;
        if (mouse[i] == CB_PRESSED && ( prev == CB_PRESSED || prev == CB_HELD )) mouse[i] = CB_HELD;

    }
}

CBinputState cbGetKeyState(int scancode) { return keys[scancode]; }
CBinputState cbGetMouseState(int scancode) { return mouse[scancode]; }

int cbIsKeyHeld(int scancode) { return keys[scancode] == CB_PRESSED || keys[scancode] == CB_HELD; }
int cbIsKeyPressed(int scancode) { return keys[scancode] == CB_PRESSED; }
int cbIsKeyReleased(int scancode) { return keys[scancode] == CB_RELEASED; }

int cbIsMouseHeld(int scancode) { return mouse[scancode] == CB_PRESSED || mouse[scancode] == CB_HELD; }
int cbIsMousePressed(int scancode) { return mouse[scancode] == CB_PRESSED; }
int cbIsMouseReleased(int scancode) { return mouse[scancode] == CB_RELEASED; }
