#pragma once
#include "Object.h"
#include "Camera.h"
#include <memory>

class Render
{
public:
    static void Start(std::shared_ptr<Camera> camera);
    static void Draw(std::shared_ptr<Object> object);
};