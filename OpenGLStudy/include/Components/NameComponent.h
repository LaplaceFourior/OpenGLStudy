#pragma once
#include "Components/BaseComponent.h"
#include <string>

class NameComponent : public BaseComponent
{
public:
    NameComponent(const std::string& name):
                mName(name)
    {}
private:
    std::string mName;
};