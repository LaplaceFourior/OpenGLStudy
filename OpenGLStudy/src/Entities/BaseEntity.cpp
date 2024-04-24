#include "Entities/BaseEntity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // for glm::decompose
#include <glm/gtc/quaternion.hpp>
#include "Components/NameComponent.h"

BaseEntity::BaseEntity(const std::string &name)
{
    createComponent<NameComponent>(name);
}

void BaseEntity::update(float deltaTime)
{
    for (const auto& component : mAllComponents) {
        component.second->update(deltaTime);
    }
}