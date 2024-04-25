#pragma once
#include "Components/LightComponent.h"

class MySpotLightComponent : public SpotLightComponent
{
    ACLASS(MySpotLightComponent, SpotLightComponent)
public:
    virtual void update(float deltaTime) override;
};