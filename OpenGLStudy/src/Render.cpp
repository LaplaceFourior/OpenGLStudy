#include "Render.h"
#include "Components/MeshComponent.h"
#include "Components/LightComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

void Render::Draw(Scene *scene)
{
    const auto& allDirectLights = scene->getObjectsWithComponents<DirectLightComponent>();
    const auto& allPointLights = scene->getObjectsWithComponents<PointLightComponent>();
    const auto& allSpotLights = scene->getObjectsWithComponents<SpotLightComponent>();
    
    std::vector<std::shared_ptr<DirectLightComponent>> allDirectLightComponents;
    for (const auto& object : scene->getObjectsWithComponents<DirectLightComponent>()) {
        auto [component] = object->getComponents<DirectLightComponent>();
        if (component->isActive()) {
            allDirectLightComponents.push_back(component);
        }
    }

    std::vector<std::shared_ptr<PointLightComponent>> allPointLightComponents;
    for (const auto& object : scene->getObjectsWithComponents<PointLightComponent>()) {
        auto [component] = object->getComponents<PointLightComponent>();
        if (component->isActive()) {
            allPointLightComponents.push_back(component);
        }
    }

    std::vector<std::shared_ptr<SpotLightComponent>> allSpotLightComponents;
    for (const auto& object : scene->getObjectsWithComponents<SpotLightComponent>()) {
        auto [component] = object->getComponents<SpotLightComponent>();
        if (component->isActive()) {
            allSpotLightComponents.push_back(component);
        }
    }


    // get the active camera
    std::shared_ptr<BaseEntity> activeCamera;
    for (auto camera : scene->getObjectsWithComponents<CameraComponent>()) {
        auto [cameraComponent] = camera->getComponents<CameraComponent>();
        if (cameraComponent->isActive()) {
            activeCamera = camera;
            break;
        }
    }

    auto [activeCameraComponent, activeCameraTransform] = activeCamera->getComponents<CameraComponent, TransformComponent>();
    
    for (const auto& object : scene->getObjectsWithComponents<TransformComponent, MeshComponent>()) {
        const auto& [transform, mesh] = object->getComponents<TransformComponent, MeshComponent>();
        const auto& material = mesh->getMaterial();
        auto shader = mesh->getShader();
        shader->applyShaderFunc(material,
                                allDirectLightComponents, allPointLightComponents, allSpotLightComponents, 
                                activeCameraTransform->getTranslation(), 
                                activeCameraComponent->getViewMatrix(), 
                                transform->getTransform());
        mesh->getMesh()->draw();
    }
}

