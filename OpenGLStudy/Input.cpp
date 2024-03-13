#include "Input.h"

GLFWwindow* Input::window = nullptr;

void Input::Init(GLFWwindow* activeWindow)
{
    window = activeWindow;
}

glm::vec2 Input::GetMousePos()
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return glm::vec2(xPos, yPos);
}