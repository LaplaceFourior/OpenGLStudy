#include "Render.h"
#include "RenderEnv.h"

std::shared_ptr<Camera> sCamera;
std::shared_ptr<RenderEnv> sRenderEnv;

void Render::Start(std::shared_ptr<Camera> camera, std::shared_ptr<RenderEnv> renderEnv)
{
    sCamera = camera;
    sRenderEnv = renderEnv;
}

void Render::Draw(std::shared_ptr<Shader> shader, std::shared_ptr<Object> object)
{
    shader->applyShaderFunc(sCamera, object, sRenderEnv);
    object->getMesh()->draw();
}