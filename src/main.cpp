#include "window.h"
#include "userInput.h"
#include "rendering.h"
#include "physics.h"
#include "utilities.h"
#include "shapeFactory.h"
#include <vector>
#include <string>

double lastFrameTime = glfwGetTime();

int main()
{
    GLFWwindow* window = initWindow(WIDTH, HEIGHT);

    ShapeFactory factory;
    std::shared_ptr<Shape> ground = factory.createShape("Ground");
    addStaticGround(WIDTH / 2, HEIGHT / 2, 0, 0, false, ground->getBinding());

    while(!glfwWindowShouldClose(window))
    {
        double currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - lastFrameTime;

        if (deltaTime >= targetFrameTime)
        {
            stepPhysics();
            processInput(window);
            renderScene();
            glfwSwapBuffers(window);
            glfwPollEvents();

            lastFrameTime = currentFrameTime;
        }
    }

    glfwTerminate();
    return 0;
}
