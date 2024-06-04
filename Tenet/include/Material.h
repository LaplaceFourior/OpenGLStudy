#pragma once
#include <memory>
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace TenetEngine {

class Material
{
public:
    Material() = default;
    ~Material() = default;
public:
    void setDiffuseTexture(std::shared_ptr<Texture> texture) { mDiffuse = texture; }
    void setSpecularTexture(std::shared_ptr<Texture> texture) { mSpecular = texture; }
    void setShininess(float shininess) { mShininess = shininess; }
    float getShininess() const { return mShininess; }
    std::shared_ptr<Texture> getDiffuseTexture() const { return mDiffuse; }
    std::shared_ptr<Texture> getSpecularTexture() const { return mSpecular; }
private:
    std::vector<std::shared_ptr<Texture>> mTextures;
    std::shared_ptr<Texture> mDiffuse;
    std::shared_ptr<Texture> mSpecular;
    float mShininess;
};

}
