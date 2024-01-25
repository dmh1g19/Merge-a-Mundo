#include "userInput.h"
#include "shape.h"
#include "physics.h"
#include "utilities.h"
#include <iostream>

bool mousePressed = false;

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Esc key pressed: Window terminated by user" << std::endl;
        glfwSetWindowShouldClose(window, true);

        delete world;
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if(!mousePressed) {
            double xpos;
            double ypos;

            glfwGetCursorPos(window, &xpos, &ypos);
            addRect(xpos, ypos, 20, 20, true); 
        }
    }
}