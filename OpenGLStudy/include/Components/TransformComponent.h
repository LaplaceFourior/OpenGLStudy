#pragma once

#include "Components/BaseComponent.h"

class TransformComponent : public BaseComponent 
{
public:
    TransformComponent() = default;
    ~TransformComponent() = default;
public:
    void setPosition(const glm::vec3& position);
    const glm::mat4& getTransform() const { return mTransform; };
private:
    glm::mat4 mTransform;

};

