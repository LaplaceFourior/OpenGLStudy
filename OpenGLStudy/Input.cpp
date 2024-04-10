#include "Input.h"

Window* Input::window = nullptr;

void Input::Init(Window* activeWindow)
{
    window = activeWindow;
}

glm::vec2 Input::GetMousePos()
{
    double xPos, yPos;
    glfwGetCursorPos(window->getNativeWindow(), &xPos, &yPos);
    return glm::vec2(xPos, yPos);
}