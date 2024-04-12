#pragma once
#include <memory>
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Material
{
public:
    Material() = default;
    ~Material() = default;
public:
    void setColor(const glm::vec4& color) { mColor = color; }
    void addTexture(std::shared_ptr<Texture> texture) { mTextures.push_back(texture); }
    std::vector<std::shared_ptr<Texture>> getTextures() const { return mTextures; };
    const glm::vec4& getColor() const { return mColor; };
private:
    std::vector<std::shared_ptr<Texture>> mTextures;
    glm::vec4 mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};