#include "eng.h"
#include "draw/draw.h"

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int actWidth = 0;
int actHeight = 0;

float CB_WIDTH = 0;
float CB_HEIGHT = 0;

dyn times;
dyn deltas;
dyn speeds;

void cbCallbackSize(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
    actWidth = width;
    actHeight = height;
    cbDrawUpdate(width,height);
}

int cbMain(
    char* title,  int width, int height,
    func init, func update, func render, func clean
) {
    //glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit()) { printf("goodbye world, never knew you!\n"); return 1; }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width,height, title, 0,0);
    if (!window) { printf("failed to create window!\n"); return 1; }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, cbCallbackSize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { printf("failed to load opengl!\n"); return 1; }

    //cbLoadGl();

    //

    glViewport(0,0,width,height);

    // windows moment (:onion:)
    glfwSetWindowSize(window, width+1,height+1);
    glfwSetWindowSize(window, width,height);
    
    glfwSwapInterval(1);

    actWidth = width;
    actHeight = height;

    //glEnable(GL_DEPTH_TEST);

    cbDynArrInit(&times);
    cbDynArrInit(&deltas);
    cbDynArrInit(&speeds);

    cbDrawSetup();

    init();

    //window our feachers
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        update();

        CB_WIDTH = actWidth;
        CB_HEIGHT = actHeight;

        cbResetTransform();
        render();
        cbDrawFlush();

        glfwSwapBuffers(window);
    }

    clean();

    cbDrawClean();

    cbDynArrFree(&speeds);
    cbDynArrFree(&deltas);
    cbDynArrFree(&times);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
