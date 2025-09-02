#ifndef SHADER_H
#define SHADER_H

unsigned int compileProgram(unsigned int* shaders, unsigned int amount);
unsigned int loadShaderFromSrc(unsigned int type, const char** src);
unsigned int loadProgramFromSrc(const char** vertSource, const char** fragSource);
unsigned int loadShader(unsigned int type, const char* path);
unsigned int loadProgram(const char* vertPath, const char* fragPath);

#endif
