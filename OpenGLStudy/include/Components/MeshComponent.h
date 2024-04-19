#pragma once

#include "BaseComponent.h"
#include "Material.h"

class MeshComponent : public BaseComponent 
{
public:
    MeshComponent() = default;
    ~MeshComponent() = default;
public:
    void setMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
    void setShader(std::shared_ptr<Shader> shader) { mShader = shader; }
    std::shared_ptr<Material> getMaterial() { return mMaterial; }
private:
    std::shared_ptr<Material> mMaterial;
    std::shared_ptr<Shader> mShader;
};