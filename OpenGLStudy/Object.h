#pragma once
#include <memory>
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

class Object
{
public:
    Object(std::shared_ptr<Shader> shader, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
    std::shared_ptr<Shader> getShader() const { return mShader; };
    std::shared_ptr<Mesh> getMesh() const { return mMesh; };
    std::shared_ptr<Material> getMaterial() const { return mMaterial; };
private:
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Material> mMaterial;
};