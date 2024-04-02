#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int heigh, const char* title);
    ~Window();
public:
    bool shouldClose() const;
private:
    GLFWwindow* mWindow = nullptr;
};