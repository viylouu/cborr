#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void cb_size(GLFWwindow* window, int width, int height) {
    glViewport(0,0, width, height);
}

int main(void) {
    if (!glfwInit()) { printf("goodbye world, never knew you!\n"); return 1; }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600, "basic window example", 0,0);
    if (!window) { printf("failed to create window!\n"); return 1; }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, cb_size);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { printf("failed to load opengl!\n"); return 1; }

    glViewport(0,0,800,600);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(.2f, .3f, .4f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
