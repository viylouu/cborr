/*#include "gl.h"

#include <stdlib.h>
#include <stdio.h>

//#include <GL/gl.h>

#ifdef _WIN32
    #include <windows.h>

    #define LOADGL(name) \
        do { \
            name = (name##_t)wglGetProcAddress(#name); \
            if (!name) { printf("failed to load %s\n", #name); return; } \
        } while(0)
#else
    #include <EGL/egl.h>
    #include <GL/glx.h>

    #define LOADGL(name) \
        do { \
            if (USES_WAYLAND) name = (name##_t)eglGetProcAddress(#name); \
            else name = (name##_t)glXGetProcAddress((const GLubyte*)#name); \
            if (!name) { printf("failed to load %s\n", #name); return; } \
        } while(0)

#endif

void cbLoadGl(void) {
    const char* USES_WAYLAND = getenv("WAYLAND_DISPLAY");
    const char* USES_X11 = getenv("DISPLAY");

    if (!USES_WAYLAND && !USES_X11) { printf("tf is this display server???\n"); return; }

    LOADGL(glCreateShader);
    LOADGL(glShaderSource);
    LOADGL(glCompileShader);
    LOADGL(glGetShaderiv);
    LOADGL(glGetShaderInfoLog);
    LOADGL(glDeleteShader);

    LOADGL(glCreateProgram);
    LOADGL(glAttachShader);
    LOADGL(glLinkProgram);
    LOADGL(glGetProgramiv);
    LOADGL(glGetProgramInfoLog);
    LOADGL(glDeleteProgram);

    LOADGL(glGenVertexArrays);
    LOADGL(glGetUniformLocation);
    LOADGL(glGenBuffers);
    LOADGL(glBindBuffer);
    LOADGL(glBufferData);
    LOADGL(glTexBuffer);

    LOADGL(glDeleteVertexArrays);
    LOADGL(glDeleteBuffers);

    LOADGL(glUseProgram);
    LOADGL(glBindVertexArray);
    LOADGL(glUniformMatrix4fv);
    LOADGL(glBufferSubData);
    LOADGL(glUniform1i);
    LOADGL(glDrawArraysInstanced);
}*/
