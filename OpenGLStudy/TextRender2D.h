#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string.h>

struct Character {
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
};

class TextRender2D
{
public:
    static void Init();
    static void LoadFonts(const std::string& filePath);
    static void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};