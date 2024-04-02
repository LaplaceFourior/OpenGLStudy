#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include "Shader.h"
#include <vector>
#include <memory>

class Panel
{
public:
    Panel(std::shared_ptr<Shader> shader, const std::string& text, const glm::vec3& color);
    ~Panel();
public:
    void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
public:
    static void Init();
    static void LoadFonts(const std::string& filePath);
private:
    glm::vec3 mPosition;
    glm::vec3 mLookAt;
    float mScale;
    std::string mText;
    glm::vec3 mColor;
    std::shared_ptr<Shader> mShader;
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> EBOs;
    std::vector<unsigned int> Textures;
};