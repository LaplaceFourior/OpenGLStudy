#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace TenetEngine {

class Window
{
public:
    Window(int width, int heigh, const char* title);
    ~Window();
public:
    bool shouldClose() const;
    void setMouseVisible(bool mouseVisible);
    void enableDepthTest(bool enableDepthTest);
    void setActive();
    void setBackgroundColor(const glm::vec4& color);
    GLFWwindow* getNativeWindow() const { return mWindow; }
    void clearCache();
    void update();
private:
    GLFWwindow* mWindow = nullptr;
    glm::vec4 mBackgroundColor = glm::vec4(0.2f, 0.5f, 0.6f, 1.0f);
};

}