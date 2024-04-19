#pragma once
#include "Components/BaseComponent.h"
#include <string>

class NameComponent : public BaseComponent
{
    friend class Scene;
    friend class BaseComponent;
private:
    NameComponent(const std::string& name):
                mName(name)
    {}
private:
    std::string mName;
};