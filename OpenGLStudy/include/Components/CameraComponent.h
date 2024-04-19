#pragma once

#include "Components/BaseComponent.h"

class CameraComponent : public BaseComponent 
{
    friend class Scene;
    friend class BaseComponent;
private:
    CameraComponent() = default;
    ~CameraComponent() = default;
};

