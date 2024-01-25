#include "window.h"
#include "userInput.h"
#include "rendering.h"
#include "physics.h"
#include "utilities.h"
#include "shape.h"

double lastFrameTime = glfwGetTime();

int main()
{
    GLFWwindow* window = initWindow(WIDTH, HEIGHT);

    initStaticGround();

    // Render loop
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
