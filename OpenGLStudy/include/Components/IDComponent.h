#pragma once
#include "BaseComponent.h"
#include "Utils/UUID.h"

class IDComponent : public BaseComponent 
{
    friend class Scene;
    friend class BaseComponent;
private:
    IDComponent() = default;
    ~IDComponent() = default;
public:
    const UUID& getID() const { return mUUID; }
private:
    UUID mUUID;
};