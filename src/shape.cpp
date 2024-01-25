#include "shape.h"
#include "rendering.h"
#include "window.h"
#include "physics.h"
#include "utilities.h"
#include <iostream>

void Square::init(std::string vertexShaderPath, std::string fragmentShaderPath) {
    initBuffers(VBO, VAO, vertices, sizeof(vertices));
    unsigned int vs = initVertexShader(vertexShaderPath);
    unsigned int fs = initFragmentShader(fragmentShaderPath);
    unsigned int sp = linkShaders(vs, fs);
    shaderProgram = sp;
}

void Square::update(const glm::vec2& position, float rotation) {
    //std::cout << "Updating position: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(rotation) << std::endl;
    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(screenCoordsToOpenGL(position), 0.0f));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(shapeSizeToOpenGL(20.0f, 20.0f), 1.0f));
    transformationMatrix = glm::rotate(transformationMatrix, rotation, glm::vec3(0.0, 0.0, 1.0));
}

void Square::render() {
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

    if (transformLoc == -1) {
        std::cerr << "Could not find uniform location for 'transform'" << std::endl;
    }
    else {
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
        drawShape(shaderProgram, VAO, 0, 6);
    }
}

std::shared_ptr<Shape> ShapeFactory::createShape(const std::string& shapeType) {
    if (shapeType == "Square") {
        return std::make_unique<Square>();
    }
    else {
        std::cout << "Unknown shape type" << std::endl;
        return nullptr; // Return nullptr to indicate an unknown shape type.
    }
}
