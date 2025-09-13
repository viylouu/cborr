/*#ifndef ENG_GL_H
#define ENG_GL_H

//#include <GL/gl.h>

#include <stddef.h>

#ifdef _WIN32
    #include <windows.h>

    #define GLFUNC(name, ret, ...) \
        typedef ret (APIENTRY *name##_t)(__VA_ARGS__); \
        static name##_t name __attribute__((unused)) = NULL
#else
    #define GLFUNC(name, ret, ...) \
        typedef ret (*name##_t)(__VA_ARGS__); \
        static name##_t name __attribute__((unused)) = NULL
#endif

// ref: https://registry.khronos.org/OpenGL/api/GL/glext.h

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef double GLdouble;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef char GLchar;

#define GL_BLEND               0x0BE2
#define GL_SRC_ALPHA           0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_TEXTURE_BUFFER      0x8C2A
#define GL_RGBA32F             0x8814
#define GL_DYNAMIC_DRAW        0x88E8
#define GL_VERTEX_SHADER       0x8B31
#define GL_FRAGMENT_SHADER     0x8B30
#define GL_TEXTURE0            0x84C0
#define GL_TEXTURE1            0x84C1

GLFUNC(glCreateShader, GLuint, GLenum type);
GLFUNC(glShaderSource, void, GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
GLFUNC(glCompileShader, void, GLuint shader);
GLFUNC(glGetShaderiv, void, GLuint shader, GLenum pname, GLint* params);
GLFUNC(glGetShaderInfoLog, void, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infolog);
GLFUNC(glDeleteShader, void, GLuint shader);

GLFUNC(glCreateProgram, GLuint, void);
GLFUNC(glAttachShader, void, GLuint program, GLuint shader);
GLFUNC(glLinkProgram, void, GLuint program);
GLFUNC(glGetProgramiv, void, GLuint program, GLenum pname, GLint* params);
GLFUNC(glGetProgramInfoLog, void, GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
GLFUNC(glDeleteProgram, void, GLuint program);

GLFUNC(glGenVertexArrays, void, GLsizei n, GLuint* arrays);
GLFUNC(glGetUniformLocation, GLint, GLuint program, const GLchar* name);
GLFUNC(glGenBuffers, void, GLsizei n, GLuint* buffers);
GLFUNC(glBindBuffer, void, GLenum target, GLuint buffer);
GLFUNC(glBufferData, void, GLenum target, GLsizeiptr size, const void* data, GLenum usage);
GLFUNC(glTexBuffer, void, GLenum target, GLenum internalformat, GLuint buffer);

GLFUNC(glDeleteVertexArrays, void, GLsizei n, const GLuint* arrays);
GLFUNC(glDeleteBuffers, void, GLsizei n, const GLuint* buffers);

GLFUNC(glUseProgram, void, GLuint program);
GLFUNC(glBindVertexArray, void, GLuint array);
GLFUNC(glUniformMatrix4fv, void, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
GLFUNC(glBufferSubData, void, GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
GLFUNC(glUniform1i, void, GLint location, GLint v0);
GLFUNC(glDrawArraysInstanced, void, GLenum mode, GLint first, GLsizei count, GLsizei instancecount);

void cbLoadGl(void);

#endif*/
