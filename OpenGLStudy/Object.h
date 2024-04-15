#pragma once
#include <memory>
#include "Mesh.h"
#include "Material.h"

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;
    std::shared_ptr<Mesh> getMesh() const { return mMesh; };
    std::shared_ptr<Material> getMaterial() const { return mMaterial; };
    const glm::mat4& getTransform() const { return mTransform; }
    void setMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; };
    void setMaterial(std::shared_ptr<Material> material) { mMaterial = material; };
    void setTransform(const glm::mat4& transform);
    const glm::vec3& getTranslation() const { return mTranslation; }
    const glm::vec3& getRotation() const { return mRotation; }
    const glm::vec3& getScale() const { return mScale; }
    void setTranslation(const glm::vec3& translation);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);
private:
    void updateTransform();
private:
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Material> mMaterial;
    glm::mat4 mTransform;
    // transform
    glm::vec3 mTranslation;
    glm::vec3 mRotation;
    glm::vec3 mScale;
};

class Light : public Object
{
public:
    void setAmbient(const glm::vec3& ambient) { mAmbient = ambient; }
    void setDiffuse(const glm::vec3& diffuse) { mDiffuse = diffuse; }
    void setSpecular(const glm::vec3& specular) { mSpecular = specular; }

    const glm::vec3& getAmbient() const { return mAmbient; }
    const glm::vec3& getDiffuse() const { return mDiffuse; }
    const glm::vec3& getSpecular() const { return mSpecular; }
private:
    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;
};