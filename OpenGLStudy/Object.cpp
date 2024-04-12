#include "Object.h"

Object::Object(std::shared_ptr<Shader> shader, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
            :mShader(shader), mMesh(mesh), mMaterial(material)
{

}