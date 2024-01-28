#include "userInput.h"
#include "shapeFactory.h"
#include "physics.h"
#include "utilities.h"
#include <iostream>
#include <thread>
#include <chrono>

bool mousePressed = false;
std::chrono::time_point<std::chrono::system_clock> lastMouseClickTime;  // Initialize a timestamp
const std::chrono::duration<float> cooldownDuration(0.2); //in seconds

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Esc key pressed: Window terminated by user" << std::endl;
        glfwSetWindowShouldClose(window, true);

        delete world;
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double xpos;
        double ypos;

        glfwGetCursorPos(window, &xpos, &ypos);
        addCircle(xpos, ypos, 30, true); 
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        auto currentTime = std::chrono::system_clock::now();

        if((currentTime - lastMouseClickTime >= cooldownDuration)) {
            double xpos;
            double ypos;

            glfwGetCursorPos(window, &xpos, &ypos);
            addRect(xpos, ypos, 30, 30, true); 

            lastMouseClickTime = currentTime;
        }
    }
}