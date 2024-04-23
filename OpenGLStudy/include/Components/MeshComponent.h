#pragma once

#include "BaseComponent.h"
#include "Material.h"
#include "Shader.h"
#include "Mesh.h"

class MeshComponent : public BaseComponent 
{
public:
    MeshComponent(std::shared_ptr<Mesh> mesh)
                :mMesh(mesh)
    {

    }
    ~MeshComponent() = default;
public:
    void setMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
    void setShader(std::shared_ptr<Shader> shader) { mShader = shader; }
    std::shared_ptr<Material> getMaterial() { return mMaterial; }
    std::shared_ptr<Shader> getShader() { return mShader; }
    std::shared_ptr<Mesh> getMesh() { return mMesh; }
    void update(float deltaTime) override;
private:
    std::shared_ptr<Material> mMaterial;
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<Mesh> mMesh;
};