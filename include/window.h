#ifndef WINDOW_H 
#define WINDOW_H  

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Application window dimensions
const int WIDTH = 640;
const int HEIGHT = 480;

// Frame rate settings
const double framesPerSecond = 60.0;
const double targetFrameTime = 1.0 / framesPerSecond;

GLFWwindow* initWindow(int, int);
void framebuffer_size_callback(GLFWwindow*, int, int);

#endif