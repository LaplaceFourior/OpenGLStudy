#include "MySpotLightComponent.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Entities/BaseEntity.h"

void MySpotLightComponent::update(float deltaTime)
{
    SpotLightComponent::update(deltaTime);
    auto [transformComp] = mBaseEntity->getComponents<TransformComponent>();
    auto [cameraComp] = mBaseEntity->getComponents<CameraComponent>();
    mPosition = transformComp->getTranslation();
}