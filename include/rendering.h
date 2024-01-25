#ifndef RENDERING_H 
#define RENDERING_H  

#include <glad/glad.h>
#include <string>

unsigned int initVertexShader(std::string&);
unsigned int initFragmentShader(std::string&);
unsigned int linkShaders(unsigned int, unsigned int);

std::string readShaderFromFile(std::string&);

void initBuffers(unsigned int&, unsigned int&, float*, size_t);
void drawShape(unsigned int, unsigned int, int, int);

#endif