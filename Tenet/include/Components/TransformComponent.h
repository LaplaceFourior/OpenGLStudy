#pragma once

#include "Components/BaseComponent.h"

namespace TenetEngine {

class TransformComponent : public BaseComponent 
{
    ACLASS(TransformComponent, BaseComponent)
public:
    TransformComponent() = default;
    ~TransformComponent() = default;
public:
    void setTransform(const glm::mat4& transform);
    void setTranslation(const glm::vec3& translation);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);
    const glm::mat4& getTransform();
    const glm::vec3& getTranslation() const { return mTranslate; }
    const glm::vec3& getRotation() const { return mRotation; }
    const glm::vec3& getScale() const { return mScale; }
    void updateTransform();
    void update(float deltaTime) override;
private:
    glm::mat4 mTransform;
    glm::vec3 mTranslate;
    glm::vec3 mRotation;
    glm::vec3 mScale = glm::vec3(1.0f, 1.0f, 1.0f);
};

}