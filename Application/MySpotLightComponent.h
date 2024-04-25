#pragma once
#include "Components/LightComponent.h"

class CameraSpotLightComponent : public SpotLightComponent
{
    ACLASS(CameraSpotLightComponent, SpotLightComponent)
public:
    virtual void update(float deltaTime) override;
};

class StableSpotLightComponent : public SpotLightComponent
{
    ACLASS(StableSpotLightComponent, SpotLightComponent)
public:
    virtual void update(float deltaTime) override;
};