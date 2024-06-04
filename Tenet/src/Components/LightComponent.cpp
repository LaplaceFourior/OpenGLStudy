#include "Components/LightComponent.h"
#include "Entities/BaseEntity.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

using namespace TenetEngine;

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
}

