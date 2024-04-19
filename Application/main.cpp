#include <iostream>
#include <math.h>
#include <memory>

#include <sstream>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"
#include "FileSystem.h"
#include "TextRender2D.h"
#include "Shader.h"
#include "Mesh.h"
#include "Panel.h"
#include "Window.h"
#include "Time.h"
#include "Texture.h"
#include "Material.h"
#include "MeshFactory.h"
#include "Render.h"
#include "Scene.h"

#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/LightComponent.h"


#define WIDTH 800
#define HEIGH 600

enum RenderThreadMode {
	RENDER_THREAD_UNSAFE,
	RENDER_THREAD_SAFE,
	RENDER_SEPARATE_THREAD
};

int main() 
{
    Window window(WIDTH, HEIGH, "finish a scene by myself");
    window.enableDepthTest(true);
    window.setMouseVisible(false);
    window.setBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // capture mouse input
    // why process mouse here? out the loop ? how to combine mouse process and keyboard process ?
    Input::Init(&window);
    Time::Init();
    MeshFactory::Init();

    Scene scene;
    auto cameraObject = scene.createObject<BaseObject>("cameraOne");
    auto cameraComponent = cameraObject->createComponent<CameraComponent>();
    auto cameraTransformComponent = cameraObject->createComponent<TransformComponent>();
    // camera settings
    cameraTransformComponent->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    cameraComponent->setLookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    
    auto boxObject = scene.createObject<BaseObject>("boxOne");
    auto boxTransformComponent = boxObject->createComponent<TransformComponent>();
    auto boxMeshComponent = boxObject->createComponent<MeshComponent>();
    
    auto boxTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box.png"));
    auto boxSpecularTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box_specular.png"));
    
    auto boxMaterial = std::make_shared<Material>();
    boxMaterial->setDiffuseTexture(boxTexture);
    boxMaterial->setSpecularTexture(boxSpecularTexture);
    boxMaterial->setShininess(50.0f);
     // create the shader
    auto defaultShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/default.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/default.fs"));
    
    defaultShader->setShaderFunc([shaderPtr = defaultShader->shared_from_this()](
        std::shared_ptr<Material> material,
        std::vector<std::shared_ptr<DirectLightComponent>> directLights,
        std::vector<std::shared_ptr<PointLightComponent>> pointLights,
        std::vector<std::shared_ptr<SpotLightComponent>> spotLights,
        const glm::vec3& cameraPosition,
        const glm::mat4& cameraTransform,
        const glm::mat4& modelTransform
    ) {
        // set the background color
        shaderPtr->use();

        material->getDiffuseTexture()->bind();
        material->getSpecularTexture()->bind();

        shaderPtr->setMat4f("model", modelTransform);
        shaderPtr->setMat4f("view", cameraTransform);
        shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
        shaderPtr->setVec3f("viewPos", cameraPosition);
        
        
        int i = 0;

        for (const auto& directLight : directLights) {    
            // Direct light
            shaderPtr->setVec3f("directLight.direction", -directLight->getDirection());
            shaderPtr->setVec3f("directLight.ambient", directLight->getAmbient());
            shaderPtr->setVec3f("directLight.diffuse", directLight->getDiffuse());
            shaderPtr->setVec3f("directLight.specular", directLight->getSpecular());  

            shaderPtr->setInt("pointLightNumber", directLights.size());
            shaderPtr->setInt("spotLightNumber", directLights.size());
        }


        for (const auto& pointLight : pointLights) {
            std::string baseName = "pointLights[" + std::to_string(i) + "]";

            shaderPtr->setVec3f((baseName + ".position").c_str(), pointLight->getPosition());
            shaderPtr->setVec3f((baseName + ".ambient").c_str(), pointLight->getAmbient());
            shaderPtr->setVec3f((baseName + ".diffuse").c_str(), pointLight->getDiffuse());
            shaderPtr->setVec3f((baseName + ".specular").c_str(), pointLight->getSpecular());
            shaderPtr->setFloat((baseName + ".constant").c_str(), pointLight->getConstant());
            shaderPtr->setFloat((baseName + ".linear").c_str(), pointLight->getLinear());
            shaderPtr->setFloat((baseName + ".quadratic").c_str(), pointLight->getQuadratic());

            i++;
        }

        i = 0;
        for (const auto& spotLight : spotLights) {
            std::string baseName = "spotLights[" + std::to_string(i) + "]";

            shaderPtr->setVec3f((baseName + ".position").c_str(), spotLight->getPosition());
            shaderPtr->setVec3f((baseName + ".direction").c_str(), spotLight->getDirection());
            shaderPtr->setFloat((baseName + ".cutOff").c_str(), spotLight->getCutOff());
            shaderPtr->setFloat((baseName + ".outCutOff").c_str(), spotLight->getOuterCutOff());
            shaderPtr->setVec3f((baseName + ".ambient").c_str(), spotLight->getAmbient());
            shaderPtr->setVec3f((baseName + ".diffuse").c_str(), spotLight->getDiffuse());
            shaderPtr->setVec3f((baseName + ".specular").c_str(), spotLight->getSpecular());

            i++;
        }

        shaderPtr->setFloat("material.shininess", material->getShininess());
        shaderPtr->setInt("material.diffuse", material->getDiffuseTexture()->getTexturePositionID());
        shaderPtr->setInt("material.specular", material->getSpecularTexture()->getTexturePositionID());
        
        
    });
    boxMeshComponent->setShader(defaultShader);
    boxMeshComponent->setMaterial(boxMaterial);

    auto lightObject = scene.createObject<BaseObject>("lightOne");
    auto lightTransformComponent = lightObject->createComponent<TransformComponent>();
    lightTransformComponent->setPosition(glm::vec3(5.0f, 5.0f, 5.0f));
    auto lightLightComponent = lightObject->createComponent<DirectLightComponent>();
    lightLightComponent->setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    lightLightComponent->setDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
    lightLightComponent->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        scene.update(Time::GetDeltaTime());
        Render::Draw(&scene);
        window.update();
    }
    
     return 0;  
}



