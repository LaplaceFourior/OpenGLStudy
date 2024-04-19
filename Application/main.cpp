// #include <iostream>
// #include <math.h>
// #include <memory>

// #include <sstream>
// #include <string>
// #include <iostream>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// #include "Camera.h"
// #include "Input.h"
// #include "FileSystem.h"
// #include "TextRender2D.h"
// #include "Shader.h"
// #include "Mesh.h"
// #include "Panel.h"
// #include "Window.h"
// #include "Time.h"
// #include "Texture.h"
// #include "Material.h"
// #include "MeshFactory.h"
// #include "Render.h"
// #include "RenderEnv.h"
// #include "Scene.h"

// #include "Components/CameraComponent.h"
// #include "Components/TransformComponent.h"

// #define WIDTH 800
// #define HEIGH 600

// enum RenderThreadMode {
// 	RENDER_THREAD_UNSAFE,
// 	RENDER_THREAD_SAFE,
// 	RENDER_SEPARATE_THREAD
// };

// int main() 
// {
//     Window window(WIDTH, HEIGH, "finish a scene by myself");
//     window.enableDepthTest(true);
//     window.setMouseVisible(false);
//     window.setBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

//     // capture mouse input
//     // why process mouse here? out the loop ? how to combine mouse process and keyboard process ?
//     Input::Init(&window);
//     Time::Init();
//     MeshFactory::Init();

//     Scene scene;
//     auto cameraObject = scene.createObject<BaseObject>("cameraOne");
//     auto cameraComponent = cameraObject->addComponent<CameraComponent>(std::make_shared<CameraComponent>());
//     auto cameraTransformComponent = cameraObject->addComponent<TransformComponent>(std::make_shared<TransformComponent>());
//     // camera settings
//     cameraTransformComponent->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
//     cameraComponent->setLookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    
//     auto boxObject = scene.createObject<BaseObject>("boxOne");
//     auto boxTransformComponent = boxObject->addComponent<TransformComponent>(std::make_shared<TransformComponent>());
//     auto boxMeshComponent = boxObject->addComponent<MeshComponent>(std::make_shared<MeshComponent>());
//     auto boxMaterialComponent = boxObject->addComponent<MaterialComponent>(std::make_shared<MaterialComponent>());
//     auto boxTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box.png"));
//     auto boxSpecularTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box_specular.png"));
//     boxMaterialComponent->setDiffuseTexture(boxTexture);
//     boxMaterialComponent->setSpecularTexture(boxSpecularTexture);
//     boxMaterialComponent->setShininess(50.0f);

//      // create the shader
//     auto defaultShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/default.vs"), 
//                             FileSystem::RelativePath("Assert/Shaders/default.fs"));
    
//     defaultShader->setShaderFunc([shaderPtr = defaultShader->shared_from_this()](std::shared_ptr<Scene> scene) {
//         // set the background color
//         shaderPtr->use();

//         object->getMaterial()->getDiffuseTexture()->bind();
//         object->getMaterial()->getSpecularTexture()->bind();

//         shaderPtr->setMat4f("model", object->getTransform());
//         shaderPtr->setMat4f("view", camera->getViewMatrix());
//         shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
        
//         const auto& directLight = renderEnv->getAllDirectLight();
//         const auto& allPointLights = renderEnv->getAllPointLights();
//         const auto& allSpotLights = renderEnv->getAllSpotLights();

//         // Direct light
//         shaderPtr->setVec3f("directLight.direction", -directLight->getTranslation());
//         shaderPtr->setVec3f("directLight.ambient", directLight->getAmbient());
//         shaderPtr->setVec3f("directLight.diffuse", directLight->getDiffuse());
//         shaderPtr->setVec3f("directLight.specular", directLight->getSpecular());  

//         shaderPtr->setInt("pointLightNumber", allPointLights.size());
//         shaderPtr->setInt("spotLightNumber", allSpotLights.size());

//         int i = 0;
//         for (const auto& pointLight : allPointLights) {
//             std::string baseName = "pointLights[" + std::to_string(i) + "]";

//             shaderPtr->setVec3f((baseName + ".position").c_str(), pointLight->getTranslation());
//             shaderPtr->setVec3f((baseName + ".ambient").c_str(), pointLight->getAmbient());
//             shaderPtr->setVec3f((baseName + ".diffuse").c_str(), pointLight->getDiffuse());
//             shaderPtr->setVec3f((baseName + ".specular").c_str(), pointLight->getSpecular());
//             shaderPtr->setFloat((baseName + ".constant").c_str(), pointLight->getConstant());
//             shaderPtr->setFloat((baseName + ".linear").c_str(), pointLight->getLinear());
//             shaderPtr->setFloat((baseName + ".quadratic").c_str(), pointLight->getQuadratic());

//             i++;
//         }

//         i = 0;
//         for (const auto& spotLight : allSpotLights) {
//             std::string baseName = "spotLights[" + std::to_string(i) + "]";

//             shaderPtr->setVec3f((baseName + ".position").c_str(), spotLight->getTranslation());
//             shaderPtr->setVec3f((baseName + ".direction").c_str(), spotLight->getDirection());
//             shaderPtr->setFloat((baseName + ".cutOff").c_str(), spotLight->getCutOff());
//             shaderPtr->setFloat((baseName + ".outCutOff").c_str(), spotLight->getOuterCutOff());
//             shaderPtr->setVec3f((baseName + ".ambient").c_str(), spotLight->getAmbient());
//             shaderPtr->setVec3f((baseName + ".diffuse").c_str(), spotLight->getDiffuse());
//             shaderPtr->setVec3f((baseName + ".specular").c_str(), spotLight->getSpecular());

//             i++;
//         }

//         shaderPtr->setFloat("material.shininess", object->getMaterial()->getShininess());
//         shaderPtr->setInt("material.diffuse", object->getMaterial()->getDiffuseTexture()->getTexturePositionID());
//         shaderPtr->setInt("material.specular", object->getMaterial()->getSpecularTexture()->getTexturePositionID());
        
        
//         shaderPtr->setVec3f("viewPos", camera->getTranslation());
//     });
//     boxMaterialComponent->setShader(defaultShader);

//     auto lightObject = scene.createObject<BaseObject>("lightOne");
//     auto lightTransformComponent = lightObject->addComponent<TransformComponent>(std::make_shared<TransformComponent>());
//     lightTransformComponent->setTransform(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 5.0f)));
//     auto lightLightComponent = lightObject->addComponent<DirectLightComponent>(std::make_shared<DirectLightComponent>());
//     lightLightComponent->setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
//     lightLightComponent->setDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
//     lightLightComponent->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

//     while (!window.shouldClose()) {
//         Time::Update();
//         window.clearCache();
//         scene.update(Time::GetDeltaTime());
//         Render::Draw(scene);
//         window.update();
//     }
    
//      return 0;  
// }

int main()
{
    
}



