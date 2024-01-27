#include "shapeFactory.h"
#include "rendering.h"
#include "window.h"
#include "physics.h"
#include "utilities.h"
#include <iostream>

void Ground::init(std::string vertexShaderPath, std::string fragmentShaderPath) {
    initBuffers(VBO, VAO, vertices, sizeof(vertices));
    shaderProgram = initShaders(vertexShaderPath, fragmentShaderPath);
}

void Ground::update(const glm::vec2& position, float rotation) {
    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(screenCoordsToOpenGL(position), 0.0f));
    //transformationMatrix = glm::scale(transformationMatrix, glm::vec3(shapeSizeToOpenGL(width, height), 1.0f));
}

void Ground::render() {
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

    if (transformLoc == -1) {
        std::cerr << "Could not find uniform location for 'transform'" << std::endl;
    }
    else {
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
        drawShape(shaderProgram, VAO, 0, 234);
    }
}

void Ground::useShaderProg() {
    useSpecificShader(shaderProgram);
}

void Ground::draw() {
    drawShape(shaderProgram, VAO, 0, 6);
}

std::vector<std::string> Ground::getBinding() {
    return groundBounding;
}

void Ground::setWidthHeight(int w, int h) {
    width = w;
    height = h;
}
