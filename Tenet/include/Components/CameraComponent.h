#pragma once

#include <memory>
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace TenetEngine {

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class CameraComponent : public BaseComponent 
{
    ACLASS(CameraComponent, BaseComponent)
public:
    CameraComponent();
    ~CameraComponent() = default;
public:
    void setLookAtTarget(const glm::vec3& lookAtTarget);
    glm::mat4 getViewMatrix() const;
    void move(Direction direction, float deltaTime);
    void turnAround(float xOffset, float yOffset);
    void update(float deltaTime) override;
    const glm::vec3& getFrontDirection() const { return cameraFrontDirection; }
private:
    void syncCameraPosition();
private:
    glm::mat4 mViewMatrix;
    float cameraSpeed = 2.0f;
    glm::vec3 cameraLookAtTarget;
    glm::vec3 cameraFrontDirection;
    glm::vec3 cameraRightDirection;
    glm::vec3 cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    std::shared_ptr<TransformComponent> mTransforComponent;

    float cameraLookSensitive = 0.05f;
    float yaw = 0.0f;
    float pitch = 0.0f;

};

}