#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"

namespace TenetEngine {

class Input
{
public:
    static glm::vec2 GetMousePos();
    static void Init(Window* window);
    static bool IsKeyPressed(int key) {
        return glfwGetKey(window->getNativeWindow(), key) == GLFW_PRESS;
    }

    static glm::vec2 GetMouseDelta() {
        static double lastX = 0, lastY = 0;
        static bool firstMouse = true;
        double xPos, yPos;
        glfwGetCursorPos(window->getNativeWindow(), &xPos, &yPos);
        if (firstMouse) 
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        glm::vec2 delta = glm::vec2(xPos - lastX, yPos - lastY);

        lastX = xPos;
        lastY = yPos;

        return delta;
    }
private:
    static Window* window;
};

}