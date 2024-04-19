#include "Objects/BaseObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // for glm::decompose
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include "Components/NameComponent.h"

// void Object::setTransform(const glm::mat4& transform)
// {
//     mTransform = transform;
//     glm::quat orientation;
//     glm::vec3 skew;
//     glm::vec4 perspective;
//     glm::decompose(transform, mScale, orientation, mTranslation, skew, perspective);

//     // Convert quaternion to Euler angles (in radians)
//     mRotation = glm::eulerAngles(orientation);
//     // Convert radians to degrees, if necessary
//     mRotation = glm::degrees(mRotation);
// }
// void Object::setTranslation(const glm::vec3& translation)
// {
//     mTranslation = translation;
// }
// void Object::setRotation(const glm::vec3& rotation)
// {
//     mRotation = rotation;
// }
// void Object::setScale(const glm::vec3& scale)
// {
//     mScale = scale;
// }

// void Object::updateTransform()
// {
//     mTransform = glm::mat4(1.0f);

//     mTransform = glm::scale(mTransform, mScale);

//     mTransform = glm::rotate(mTransform, glm::radians(mRotation.x), glm::vec3(1, 0, 0));
//     mTransform = glm::rotate(mTransform, glm::radians(mRotation.y), glm::vec3(0, 1, 0));
//     mTransform = glm::rotate(mTransform, glm::radians(mRotation.z), glm::vec3(0, 0, 1));

//     mTransform = glm::translate(mTransform, mTranslation);
// }

// addComponent<NameComponent>(std::make_shared<NameComponent>(name));