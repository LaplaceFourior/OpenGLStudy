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
    void addTexture(std::shared_ptr<Texture> texture) { mTextures.push_back(texture); }
    void setAmbient(const glm::vec3& ambient) { mAmbient = ambient; }
    void setDiffuse(const glm::vec3& diffuse) { mDiffuse = diffuse; }
    void setSpecular(const glm::vec3& specular) { mSpecular = specular; }
    void setShininess(float shininess) { mShininess = shininess; }

    std::vector<std::shared_ptr<Texture>> getTextures() const { return mTextures; };
    float getShininess() const { return mShininess; }
    const glm::vec3& getAmbient() const { return mAmbient; }
    const glm::vec3& getDiffuse() const { return mDiffuse; }
    const glm::vec3& getSpecular() const { return mSpecular; }
    glm::vec3 getColor();
private:
    std::vector<std::shared_ptr<Texture>> mTextures;
    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;
    float mShininess;
};

class LightMaterial : public Material
{
public:
    void setLightColor(const glm::vec3& lightColor) { mColor = lightColor; }
    const glm::vec3& getLightColor() const { return mColor; }
private:
    glm::vec3 mColor;
};