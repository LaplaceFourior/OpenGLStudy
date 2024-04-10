#include "Window.h"
#include <iostream>
#include "Input.h"

static uint32_t sGLFWWindowCount = 0;

Window::Window(int width, int heigh, const char* title)
{
    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
    mWindow = glfwCreateWindow(800, 600, title, NULL, NULL);
    setActive();
    //error check
    if (mWindow == NULL) {
        // log error message
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    } 
    // glad: load all opengl functions' pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // log error message
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    ++sGLFWWindowCount;
}

Window::~Window()
{
    glfwDestroyWindow(mWindow);
    --sGLFWWindowCount;

    if (sGLFWWindowCount == 0) {
        glfwTerminate();
    }
}
void Window::enableDepthTest(bool enableDepthTest)
{
    if (enableDepthTest) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}
void Window::setActive() 
{
    glfwMakeContextCurrent(mWindow);
}
void Window::setBackgroundColor(const glm::vec4 &color)
{
    mBackgroundColor = color;
}
bool Window::shouldClose() const
{
    return (glfwWindowShouldClose(mWindow));
}

void Window::setMouseVisible(bool mouseVisible)
{
    if ( mouseVisible ) {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Window::clearCache()
{
    glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, mBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(mWindow, true);
    }
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}