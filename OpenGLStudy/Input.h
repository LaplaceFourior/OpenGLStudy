#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Input
{
public:
    static glm::vec2 GetMousePos();
    static void Init(GLFWwindow* window);
private:
    static GLFWwindow* window;
};