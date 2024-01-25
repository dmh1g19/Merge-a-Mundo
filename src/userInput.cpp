#include "userInput.h"
#include "shape.h"
#include "physics.h"
#include <iostream>

bool squareInit = false;
bool aKeyPressed = false;
bool mousePressed = false;

int objectWidthPixels = 20;
int objectHeightPixels = 20;

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Esc key pressed: Window terminated by user" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if(!aKeyPressed) {
            std::cout << "'a' key pressed, screen cleared" << std::endl;
            // Change background colour of window
            glClear(GL_COLOR_BUFFER_BIT);
            aKeyPressed = true;
        }
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if(!mousePressed) {
            double xpos;
            double ypos;

            glfwGetCursorPos(window, &xpos, &ypos);
            b2Body* body = addRect(xpos, ypos, objectWidthPixels, objectHeightPixels, true); 
        }
    }
}