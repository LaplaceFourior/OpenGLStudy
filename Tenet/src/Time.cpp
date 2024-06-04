#include "Time.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace TenetEngine;

float Time::lastFrameTime = 0.0f;
float Time::deltaTime = 0.0f;

void Time::Init() {
    lastFrameTime = glfwGetTime();
}

float Time::GetDeltaTime() {
    return deltaTime;
}

void Time::Update() {
    float currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}