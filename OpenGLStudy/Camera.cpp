#include "Camera.h"

void Camera::setLookAtTarget(const glm::vec3& lookAtTarget)
{
    cameraLookAtTarget = lookAtTarget;
    cameraFrontDirection = glm::normalize(cameraLookAtTarget - cameraPosition);
    cameraRightDirection = glm::cross(cameraFrontDirection, cameraUpDirection);
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