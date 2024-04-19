#include "Components/CameraComponent.h"
#include "Input.h"

void CameraComponent::setLookAtTarget(const glm::vec3 &lookAtTarget)
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

glm::mat4 CameraComponent::getViewMatrix() const
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
}
void CameraComponent::move(Direction direction, float deltaTime)
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

void CameraComponent::turnAround(float xOffset, float yOffset)
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

void CameraComponent::update(float deltaTime)
{
    if (Input::IsKeyPressed(GLFW_KEY_W)) {
        move(Direction::FORWARD, deltaTime);
    }
    if (Input::IsKeyPressed(GLFW_KEY_S)) {
        move(Direction::BACKWARD, deltaTime);
    }
    if (Input::IsKeyPressed(GLFW_KEY_A)) {
        move(Direction::LEFT, deltaTime);
    }
    if (Input::IsKeyPressed(GLFW_KEY_D)) {
        move(Direction::RIGHT, deltaTime);
    }

    glm::vec2 mouseDelta = Input::GetMouseDelta();
    turnAround(-mouseDelta.x, -mouseDelta.y);
}

void CameraComponent::syncCameraPosition()
{
    
}