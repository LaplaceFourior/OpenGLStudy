#include "Render.h"

std::shared_ptr<Camera> sCamera;

void Render::Start(std::shared_ptr<Camera> camera)
{
    sCamera = camera;
}

void Render::Draw(std::shared_ptr<Shader> shader, std::shared_ptr<Object> object)
{
    shader->applyShaderFunc(sCamera, object);
    object->getMesh()->draw();
}