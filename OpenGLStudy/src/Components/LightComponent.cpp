#include "Components/LightComponent.h"
#include "Objects/BaseObject.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

void LightComponent::update(float deltaTime)
{
    BaseComponent::update(deltaTime);
}

void DirectLightComponent::update(float deltaTime)
{
    LightComponent::update(deltaTime);
}

void PointLightComponent::update(float deltaTime)
{
    LightComponent::update(deltaTime);
}

void SpotLightComponent::update(float deltaTime)
{
    LightComponent::update(deltaTime);
    auto [transformComp] = mBaseObject->getComponents<TransformComponent>();
    auto [cameraComp] = mBaseObject->getComponents<CameraComponent>();
    mPosition = transformComp->getTranslation();
    // direction = cameraComp->getFrontDirection();
}

