#include "MySpotLightComponent.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Entities/BaseEntity.h"

void CameraSpotLightComponent::update(float deltaTime)
{
    SpotLightComponent::update(deltaTime);
    auto [transformComp] = mBaseEntity->getComponents<TransformComponent>();
    auto [cameraComp] = mBaseEntity->getComponents<CameraComponent>();
    mPosition = transformComp->getTranslation();
    direction = cameraComp->getFrontDirection();
}

void StableSpotLightComponent::update(float deltaTime)
{
    SpotLightComponent::update(deltaTime);
    auto [transformComp] = mBaseEntity->getComponents<TransformComponent>();
    mPosition = transformComp->getTranslation();
}