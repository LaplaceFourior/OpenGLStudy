#pragma once
#include <memory>
#include "Mesh.h"
#include "Material.h"

class Object
{
public:
    Object() = default;
    ~Object() = default;
    std::shared_ptr<Mesh> getMesh() const { return mMesh; };
    std::shared_ptr<Material> getMaterial() const { return mMaterial; };
    const glm::mat4& getTransform() const { return mTransform; }
    void setMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; };
    void setMaterial(std::shared_ptr<Material> material) { mMaterial = material; };
    void setTransform(const glm::mat4& transform) { mTransform = transform; }
private:
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Material> mMaterial;
    glm::mat4 mTransform;
};