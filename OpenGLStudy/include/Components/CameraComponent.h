#pragma once

#include "Components/BaseComponent.h"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class CameraComponent : public BaseComponent 
{
public:
    CameraComponent() = default;
    ~CameraComponent() = default;
public:
    void setLookAtTarget(const glm::vec3& lookAtTarget);
    glm::mat4 getViewMatrix() const;
    void move(Direction direction, float deltaTime);
    void turnAround(float xOffset, float yOffset);
    void update(float deltaTime);
private:
    void syncCameraPosition();
private:
    glm::mat4 mViewMatrix;
    float cameraSpeed = 2.0f;
    glm::vec3 cameraPosition;
    glm::vec3 cameraLookAtTarget;
    glm::vec3 cameraFrontDirection;
    glm::vec3 cameraRightDirection;
    glm::vec3 cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    float cameraLookSensitive = 0.05f;
    float yaw = 0.0f;
    float pitch = 0.0f;

};

