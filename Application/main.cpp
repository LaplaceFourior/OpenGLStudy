#include <iostream>
#include <math.h>
#include <memory>

#include <sstream>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Register.h"
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
#include "MySpotLightComponent.h"
#include "RegisterTypes.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define WIDTH 800
#define HEIGH 600

using namespace TenetEngine;

enum RenderThreadMode {
	RENDER_THREAD_UNSAFE,
	RENDER_THREAD_SAFE,
	RENDER_SEPARATE_THREAD
};

int main() 
{
    registerTypes();
    REGISTER_CLASS(StableSpotLightComponent)
    REGISTER_CLASS(CameraSpotLightComponent)
    Window window(WIDTH, HEIGH, "finish a scene by myself");
    window.setActive();
    window.enableDepthTest(true);
    window.setMouseVisible(false);
    window.setBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // capture mouse input
    Input::Init(&window);
    Time::Init();
    MeshFactory::Init();

    Scene scene;
    auto cameraObject = scene.createObject<BaseEntity>("cameraOne");
    auto cameraTransformComponent = cameraObject->createComponent<TransformComponent>();
    auto cameraComponent = cameraObject->createComponent<CameraComponent>();
    // camera settings
    cameraTransformComponent->setTranslation(glm::vec3(0.0f, 0.0f, 3.0f));
    cameraComponent->setLookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    auto lightComp = cameraObject->createComponent<CameraSpotLightComponent>();
    lightComp->setAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
    lightComp->setDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
    lightComp->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    lightComp->setCutOff(glm::cos(glm::radians(10.5f)));
    lightComp->setOuterCutOff(glm::cos(glm::radians(12.5f)));
    lightComp->setActive(true);
    
     // create the shader
    auto defaultShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/default.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/default.fs"));
    
    defaultShader->setShaderFunc([shaderPtr = defaultShader->shared_from_this()](
        std::shared_ptr<Material> material,
        std::vector<std::shared_ptr<DirectLightComponent>> directLights,
        std::vector<std::shared_ptr<PointLightComponent>> pointLights,
        std::vector<std::shared_ptr<SpotLightComponent>> spotLights,
        const glm::vec3& cameraPosition,
        const glm::mat4& viewMatrix,
        const glm::mat4& modelMatrix
    ) {
        // set the background color
        shaderPtr->use();

        material->getDiffuseTexture()->bind();
        material->getSpecularTexture()->bind();

        shaderPtr->setMat4f("model", modelMatrix);
        shaderPtr->setMat4f("view", viewMatrix);
        shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
        shaderPtr->setVec3f("viewPos", cameraPosition);
        
        
        int i = 0;

        for (const auto& directLight : directLights) {    
            // Direct light
            std::string baseName = "directLights[" + std::to_string(i) + "]";

            shaderPtr->setVec3f((baseName + ".direction").c_str(), -directLight->getDirection());
            shaderPtr->setVec3f((baseName + ".ambient").c_str(), directLight->getAmbient());
            shaderPtr->setVec3f((baseName + ".diffuse").c_str(), directLight->getDiffuse());
            shaderPtr->setVec3f((baseName + ".specular").c_str(), directLight->getSpecular());  

            i++;
        }

        i = 0;
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
        // vec3 position;
        // vec3 direction;
        // float cutOff;
        // float outerCutOff;

        // vec3 ambient;
        // vec3 diffuse;
        // vec3 specular;
        for (const auto& spotLight : spotLights) {
            std::string baseName = "spotLights[" + std::to_string(i) + "]";

            shaderPtr->setVec3f((baseName + ".position").c_str(), spotLight->getPosition());
            shaderPtr->setVec3f((baseName + ".direction").c_str(), spotLight->getDirection());
            shaderPtr->setFloat((baseName + ".cutOff").c_str(), spotLight->getCutOff());
            shaderPtr->setFloat((baseName + ".outerCutOff").c_str(), spotLight->getOuterCutOff());
            shaderPtr->setVec3f((baseName + ".ambient").c_str(), spotLight->getAmbient());
            shaderPtr->setVec3f((baseName + ".diffuse").c_str(), spotLight->getDiffuse());
            shaderPtr->setVec3f((baseName + ".specular").c_str(), spotLight->getSpecular());

            i++;
        }

        shaderPtr->setFloat("material.shininess", material->getShininess());
        shaderPtr->setInt("material.diffuse", material->getDiffuseTexture()->getTexturePositionID());
        shaderPtr->setInt("material.specular", material->getSpecularTexture()->getTexturePositionID());
        
        shaderPtr->setInt("directLightNumber", directLights.size());
        shaderPtr->setInt("pointLightNumber", pointLights.size());
        shaderPtr->setInt("spotLightNumber", spotLights.size());
        
    });
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    for (unsigned int i = 0; i < 10; i++)
    {
        const std::string& boxName = "box-" + std::to_string(i);
        auto boxObject = scene.createObject<BaseEntity>(boxName);
        auto boxTransformComponent = boxObject->createComponent<TransformComponent>();
        boxTransformComponent->setTranslation(cubePositions[i]);
        boxTransformComponent->setRotation(cubePositions[i]*cubePositions[i]);
        auto boxMeshComponent = boxObject->createComponent<MeshComponent>(MeshFactory::GetBoxMesh());
        
        auto boxTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box.png"));
        auto boxSpecularTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box_specular.png"));
        
        auto boxMaterial = std::make_shared<Material>();
        boxMaterial->setDiffuseTexture(boxTexture);
        boxMaterial->setSpecularTexture(boxSpecularTexture);
        boxMaterial->setShininess(50.0f);
        boxMeshComponent->setShader(defaultShader);
        boxMeshComponent->setMaterial(boxMaterial);
    }


    // direct light 
    auto directLightObj = scene.createObject<BaseEntity>("lightOne");
    auto directLightLight = directLightObj->createComponent<DirectLightComponent>();
    directLightLight->setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    directLightLight->setDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
    directLightLight->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    directLightLight->setDirection(glm::vec3(-3.0f, -3.0f, -3.0f));
    directLightLight->setActive(false);
    // create the light cube
    auto lightShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/Light.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/Light.fs"));
    lightShader->setShaderFunc([shaderPtr = lightShader->shared_from_this()](
            std::shared_ptr<Material> material,
            std::vector<std::shared_ptr<DirectLightComponent>> directLights,
            std::vector<std::shared_ptr<PointLightComponent>> pointLights,
            std::vector<std::shared_ptr<SpotLightComponent>> spotLights,
            const glm::vec3& cameraPosition,
            const glm::mat4& viewMatrix,
            const glm::mat4& modelMatrix)
        {
        shaderPtr->use();
        shaderPtr->setVec3f("color", glm::vec3(1.0f, 1.0f, 1.0f));
        shaderPtr->setMat4f("model", modelMatrix);
        shaderPtr->setMat4f("view", viewMatrix);
        shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
    });
    // point light
    auto pointLightObj = scene.createObject<BaseEntity>("lightTwo");
    auto pointLightTran = pointLightObj->createComponent<TransformComponent>();
    pointLightTran->setTranslation(glm::vec3(0.0f, 0.0f, -3.0f));
    pointLightTran->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
    auto pointLightLight = pointLightObj->createComponent<PointLightComponent>();
    pointLightLight->setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
    pointLightLight->setConstant(1.0f);
    pointLightLight->setDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
    pointLightLight->setLinear(0.09f);
    pointLightLight->setQuadratic(0.032f);
    pointLightLight->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    auto pointLightMesh = pointLightObj->createComponent<MeshComponent>(MeshFactory::GetBoxMesh());
    pointLightMesh->setShader(lightShader);

    auto spotLight = scene.createObject<BaseEntity>("lightThree");
    auto spotLightTran = spotLight->createComponent<TransformComponent>();
    spotLightTran->setTranslation(glm::vec3(-3.0f, 0.0f, 0.0f));
    spotLightTran->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
    auto spotLightLight = spotLight->createComponent<StableSpotLightComponent>();
    spotLightLight->setAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
    spotLightLight->setDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
    spotLightLight->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    spotLightLight->setCutOff(glm::cos(glm::radians(10.5f)));
    spotLightLight->setOuterCutOff(glm::cos(glm::radians(12.5f)));
    spotLightLight->setDirection(glm::vec3(1.0f, 0.0f, 0.0f));    
    spotLightLight->setActive(true);
    auto spotLightMesh = spotLight->createComponent<MeshComponent>(MeshFactory::GetBoxMesh());
    spotLightMesh->setShader(lightShader);

    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        scene.update(Time::GetDeltaTime());
        Render::Draw(&scene);
        window.update();
    }
    
    return 0;  
}



