#pragma once

#include "Components/BaseComponent.h"

class TransformComponent : public BaseComponent 
{
    friend class Scene;
    friend class BaseComponent;
private:
    TransformComponent() = default;
    ~TransformComponent() = default;
};

