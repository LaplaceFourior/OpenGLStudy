#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera() = default;
    void setPosition(const glm::vec3& position);
    void setLookAtTarget(const glm::vec3& lookAtTarget);
    glm::mat4 getViewMatrix() const;
    void move(Direction direction, float deltaTime);
private:
    float cameraSpeed = 2.0f;
    glm::vec3 cameraPosition;
    glm::vec3 cameraLookAtTarget;
    glm::vec3 cameraFrontDirection;
    glm::vec3 cameraRightDirection;
    glm::vec3 cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
};