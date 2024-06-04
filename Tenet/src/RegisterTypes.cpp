#include "RegisterTypes.h"
#include "Register.h"
#include "Components/BaseComponent.h"
#include "Components/CameraComponent.h"
#include "Components/LightComponent.h"
#include "Components/MeshComponent.h"
#include "Components/TransformComponent.h"

using namespace TenetEngine;

// global functions
void TenetEngine::registerTypes()
{
    REGISTER_CLASS(BaseComponent)
    REGISTER_CLASS(CameraComponent)
    REGISTER_CLASS(LightComponent)
    REGISTER_CLASS(DirectLightComponent)
    REGISTER_CLASS(SpotLightComponent)
    REGISTER_CLASS(MeshComponent)
    REGISTER_CLASS(TransformComponent)
}