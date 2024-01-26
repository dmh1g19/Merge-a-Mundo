#include "utilities.h"
#include <iomanip> // for std::setw

// OpenGL uses NDC where [-1,1] for device independence for display

// Normalize the screen coordinates to NDC
glm::vec2 screenCoordsToOpenGL(const glm::vec2& screenCoords) {
    float x = (screenCoords.x / WIDTH) * 2.0f - 1.0f;
    float y = 1.0f - (screenCoords.y / HEIGHT) * 2.0f;

    return glm::vec2(x, y);
}

// Scale the object to NDC
glm::vec2 shapeSizeToOpenGL(float w, float h) {
    float wScaled = (w / WIDTH) * 2.0f;
    float hScaled = (h / HEIGHT) * 2.0f;
    
    return glm::vec2(wScaled, hScaled);
}

// OpenGL uses pixels, Box2D uses meters

float pixels2Meters(float n) {
    return P2M * n;
}

float meters2Pixels(float n) {
    return M2P * n;
}

// For printing the results of shader transformation matrices
void printShaderProgramMatrix(glm::mat4 transformationMatrix) {
    std::cout << "Transformation Matrix:" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << std::setw(10) << transformationMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}