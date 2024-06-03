#pragma once
#include "BaseComponent.h"
#include "Utils/UUID.h"

class IDComponent : public BaseComponent 
{
    ACLASS(IDComponent, BaseComponent)
public:
    IDComponent() = default;
    ~IDComponent() = default;
friend class Scene;
friend class BaseComponent;
public:
    const UUID& getID() const { return mUUID; }
private:
    UUID mUUID;
};