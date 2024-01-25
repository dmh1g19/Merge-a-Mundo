#include "shape.h"
#include "rendering.h"
#include "window.h"
#include "physics.h"
#include <cmath>
#include <iostream>
#include <iomanip> // for std::setw

void Square::init(int x , int y, std::string vertexShaderPath, std::string fragmentShaderPath) {
    initBuffers(VBO, VAO, vertices, sizeof(vertices));
    unsigned int vs = initVertexShader(vertexShaderPath);
    unsigned int fs = initFragmentShader(fragmentShaderPath);
    unsigned int sp = linkShaders(vs, fs);
    shaderProgram = sp;
}

// Normalize the screen coordinates to NDC where [-1,1] for device independence for display
glm::vec2 ScreenCoordsToOpenGL(const glm::vec2& screenCoords) {
    float x = (screenCoords.x / WIDTH) * 2.0f - 1.0f;
    float y = 1.0f - (screenCoords.y / HEIGHT) * 2.0f;

    return glm::vec2(x, y);
}

// Scale the object
glm::vec2 scalePixelsToOpenGL(float w, float h) {
    float wScaled = (w / WIDTH) * 2.0f;
    float hScaled = (h / HEIGHT) * 2.0f;
    
    return glm::vec2(wScaled, hScaled);
}

void Square::update(const glm::vec2& position, float rotation) {
    //std::cout << "Updating position: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(rotation) << std::endl;

    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(ScreenCoordsToOpenGL(position), 0.0f));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scalePixelsToOpenGL(20.0f, 20.0f), 1.0f));
    transformationMatrix = glm::rotate(transformationMatrix, rotation, glm::vec3(0.0, 0.0, 1.0));

    
    //std::cout << "Transformation Matrix:" << std::endl;
    //for (int i = 0; i < 4; i++) {
    //    for (int j = 0; j < 4; j++) {
    //        std::cout << std::setw(10) << transformationMatrix[i][j] << " ";
    //    }
    //    std::cout << std::endl;
    //}
}

void Square::render() {
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

    if (transformLoc == -1) {
        std::cerr << "Could not find uniform location for 'transform'" << std::endl;
    }

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));

    drawShape(shaderProgram, VAO, 0, 6);
}

std::shared_ptr<Shape> ShapeFactory::createShape(const std::string& shapeType) {
    if (shapeType == "Square") {
        return std::make_unique<Square>();
    }
    else {
        std::cout << "Unknown shape type" << std::endl;
    }
}
