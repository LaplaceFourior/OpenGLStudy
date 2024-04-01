#include "Camera.h"
#include <iostream>
void Camera::setLookAtTarget(const glm::vec3& lookAtTarget)
{
    cameraLookAtTarget = lookAtTarget;
    cameraFrontDirection = glm::normalize(cameraLookAtTarget - cameraPosition);
    cameraRightDirection = glm::cross(cameraFrontDirection, cameraUpDirection);

    float x = cameraFrontDirection.x;
    float y = cameraFrontDirection.y;
    float z = cameraFrontDirection.z;
    
    pitch = glm::degrees(glm::asin(y));
    yaw = glm::degrees(glm::atan(z, x));
}
void Camera::setPosition(const glm::vec3& position)
{
    cameraPosition = position;
}
glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
}
void Camera::move(Direction direction, float deltaTime)
{
    float speed = cameraSpeed * deltaTime;

    if( direction == Direction::FORWARD ) {
        cameraPosition += speed * cameraFrontDirection; 
    }
    
    if( direction == Direction::BACKWARD ) {
        cameraPosition -= speed * cameraFrontDirection; 
    }
    
    if( direction == Direction::LEFT ) {
        cameraPosition -= speed * cameraRightDirection; 
    }

    if( direction == Direction::RIGHT ) {
        cameraPosition += speed * cameraRightDirection;
    }
}

void Camera::turnAround(float xOffset, float yOffset)
{
    yaw += cameraLookSensitive * xOffset;
    pitch += cameraLookSensitive * yOffset;
    if (pitch > 90.0f) {
        pitch = 90.0f;
    }
    if (pitch < -90.0f) {
        pitch = -90.0f;
    }
    float y = glm::sin(glm::radians(pitch));
    float x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(180 - yaw));
    float z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(180 - yaw));
    cameraFrontDirection = glm::vec3(x, y, z);
    cameraRightDirection = glm::cross(cameraFrontDirection, cameraUpDirection);
}