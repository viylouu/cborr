#include "eng.h"
#include "draw/draw.h"

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int actWidth = 0;
int actHeight = 0;

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
    if (!glfwInit()) { printf("goodbye world, never knew you!\n"); return 1; }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width,height, title, 0,0);
    if (!window) { printf("failed to create window!\n"); return 1; }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, cbCallbackSize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { printf("failed to load opengl!\n"); return 1; }

    glViewport(0,0,width,height);
    
    glfwSwapInterval(1);

    actWidth = width;
    actHeight = height;

    glEnable(GL_DEPTH_TEST);

    cbDrawSetup();

    init();

    //window our feachers
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        update();

        cbResetTransform();
        render();
        cbDrawFlush();

        glfwSwapBuffers(window);
    }

    clean();

    cbDrawClean();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
