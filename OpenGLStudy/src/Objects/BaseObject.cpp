#include "Objects/BaseObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // for glm::decompose
#include <glm/gtc/quaternion.hpp>
#include "Components/NameComponent.h"
#include "Objects/BaseObject.h"

BaseObject::BaseObject(const std::string &name)
{
    createComponent<NameComponent>(name);
}

void BaseObject::update(float deltaTime)
{
    for (const auto& component : mAllComponents) {
        component.second->update(deltaTime);
    }
}