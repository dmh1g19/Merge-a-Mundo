#include "shapeFactory.h"
#include "rendering.h"
#include "window.h"
#include "physics.h"
#include "utilities.h"
#include <iostream>

unsigned int squareGlobalShaderProg;

void Square::init(std::string vertexShaderPath, std::string fragmentShaderPath) {
    initBuffers(VBO, VAO, vertices, sizeof(vertices));

    if(!squareGlobalShaderProg) {
        std::cout << "Gobal square shader initialized" << std::endl;
        squareGlobalShaderProg = initShaders(vertexShaderPath, fragmentShaderPath);
    }
    else {
        std::cout << "Using gobal square shader program" << std::endl;
    }
}

void Square::update(const glm::vec2& position, float rotation) {
    //std::cout << "Updating position: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(rotation) << std::endl;
    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(screenCoordsToOpenGL(position), 0.0f));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(shapeSizeToOpenGL(width, height), 1.0f));
    transformationMatrix = glm::rotate(transformationMatrix, rotation, glm::vec3(0.0, 0.0, 1.0));
}

void Square::render() {
    unsigned int transformLoc = glGetUniformLocation(squareGlobalShaderProg, "transform");

    if (transformLoc == -1) {
        std::cerr << "Could not find uniform location for 'transform'" << std::endl;
    }
    else {
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    }
}

void Square::useShaderProg() {
    useSpecificShader(squareGlobalShaderProg);
}

void Square::draw() {
    drawShape(squareGlobalShaderProg, VAO, 0, 6);
}

void Square::setWidthHeight(int w, int h) {
    width = w;
    height = h;
}

std::vector<std::string> Square::getBinding() {
}