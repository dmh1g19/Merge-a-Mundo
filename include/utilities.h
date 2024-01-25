#ifndef UTILITIES_H
#define UTILITIES_H

#include "window.h"
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <iostream>

// OpenGL uses pixels, Box2D uses meters

// Conversion constants between meters and pixels
const float M2P = 20.0f;
const float P2M = 1.0f / M2P;

glm::vec2 screenCoordsToOpenGL(const glm::vec2&);
glm::vec2 shapeSizeToOpenGL(float, float);

float pixels2Meters(float);
float meters2Pixels(float);

void printShaderProgramMatrix(glm::mat4 transformationMatrix);

#endif // UTILITIES_H
