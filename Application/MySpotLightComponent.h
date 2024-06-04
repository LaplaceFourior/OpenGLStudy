#pragma once
#include "Components/LightComponent.h"

namespace TenetEngine {

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

}