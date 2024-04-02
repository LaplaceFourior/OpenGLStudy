#include "Window.h"
#include <iostream>

Window::Window(int width, int heigh, const char* title)
{
    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
    mWindow = glfwCreateWindow(800, 600, "finish a scene by myself", NULL, NULL);
    //error check
    if (mWindow == NULL) {
        // log error message
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    } 
    glfwMakeContextCurrent(mWindow);
    // enable depth test to create 3D graph
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glad: load all opengl functions' pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // log error message
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

bool Window::shouldClose() const
{
    return (!glfwWindowShouldClose(mWindow));
}