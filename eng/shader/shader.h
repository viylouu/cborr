#ifndef SHADER_H
#define SHADER_H

unsigned int cbCompileProgram(unsigned int* shaders, unsigned int amount);
unsigned int cbLoadShaderFromSrc(unsigned int type, const char** src);
unsigned int cbLoadProgramFromSrc(const char** vertSource, const char** fragSource);
unsigned int cbLoadShader(unsigned int type, const char* path);
unsigned int cbLoadProgram(const char* vertPath, const char* fragPath);

#endif
