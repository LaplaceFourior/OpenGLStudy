#pragma once
#include "Object.h"
#include "Camera.h"
#include <memory>
#include "Shader.h"

class Render
{
public:
    static void Start(std::shared_ptr<Camera> camera, std::shared_ptr<RenderEnv> renderEnv);
    static void Draw(std::shared_ptr<Shader> shader, std::shared_ptr<Object> object);
};