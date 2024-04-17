#include <iostream>
#include <math.h>
#include <memory>

#include <sstream>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
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
#include "Object.h"
#include "MeshFactory.h"
#include "Render.h"
#include "RenderEnv.h"

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
    // camera settings
    auto camera = std::make_shared<Camera>();
    camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    camera->setLookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    
    auto renderEnv = std::make_shared<RenderEnv>();

    // create the shader
    auto defaultShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/default.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/default.fs"));
    
    defaultShader->setShaderFunc([shaderPtr = defaultShader->shared_from_this()](std::shared_ptr<Camera> camera, 
                                                                                std::shared_ptr<Object> object,
                                                                                std::shared_ptr<RenderEnv> renderEnv) {
        // set the background color
        shaderPtr->use();

        object->getMaterial()->getDiffuseTexture()->bind();
        object->getMaterial()->getSpecularTexture()->bind();

        shaderPtr->setMat4f("model", object->getTransform());
        shaderPtr->setMat4f("view", camera->getViewMatrix());
        shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
        
        const auto& directLight = renderEnv->getAllDirectLight();
        const auto& allPointLights = renderEnv->getAllPointLights();
        const auto& allSpotLights = renderEnv->getAllSpotLights();

        // Direct light
        shaderPtr->setVec3f("directLight.direction", -directLight->getTranslation());
        shaderPtr->setVec3f("directLight.ambient", directLight->getAmbient());
        shaderPtr->setVec3f("directLight.diffuse", directLight->getDiffuse());
        shaderPtr->setVec3f("directLight.specular", directLight->getSpecular());  

        shaderPtr->setInt("pointLightNumber", allPointLights.size());
        shaderPtr->setInt("spotLightNumber", allSpotLights.size());

        int i = 0;
        for (const auto& pointLight : allPointLights) {
            std::string baseName = "pointLights[" + std::to_string(i) + "]";

            shaderPtr->setVec3f((baseName + ".position").c_str(), pointLight->getTranslation());
            shaderPtr->setVec3f((baseName + ".ambient").c_str(), pointLight->getAmbient());
            shaderPtr->setVec3f((baseName + ".diffuse").c_str(), pointLight->getDiffuse());
            shaderPtr->setVec3f((baseName + ".specular").c_str(), pointLight->getSpecular());
            shaderPtr->setFloat((baseName + ".constant").c_str(), pointLight->getConstant());
            shaderPtr->setFloat((baseName + ".linear").c_str(), pointLight->getLinear());
            shaderPtr->setFloat((baseName + ".quadratic").c_str(), pointLight->getQuadratic());

            i++;
        }

        i = 0;
        for (const auto& spotLight : allSpotLights) {
            std::string baseName = "spotLights[" + std::to_string(i) + "]";

            shaderPtr->setVec3f((baseName + ".position").c_str(), spotLight->getTranslation());
            shaderPtr->setVec3f((baseName + ".direction").c_str(), spotLight->getDirection());
            shaderPtr->setFloat((baseName + ".cutOff").c_str(), spotLight->getCutOff());
            shaderPtr->setFloat((baseName + ".outCutOff").c_str(), spotLight->getOuterCutOff());
            shaderPtr->setVec3f((baseName + ".ambient").c_str(), spotLight->getAmbient());
            shaderPtr->setVec3f((baseName + ".diffuse").c_str(), spotLight->getDiffuse());
            shaderPtr->setVec3f((baseName + ".specular").c_str(), spotLight->getSpecular());

            i++;
        }

        shaderPtr->setFloat("material.shininess", object->getMaterial()->getShininess());
        shaderPtr->setInt("material.diffuse", object->getMaterial()->getDiffuseTexture()->getTexturePositionID());
        shaderPtr->setInt("material.specular", object->getMaterial()->getSpecularTexture()->getTexturePositionID());
        
        
        shaderPtr->setVec3f("viewPos", camera->getTranslation());
    });

    auto boxTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box.png"));
    auto boxSpecularTexture = std::make_shared<Texture>(FileSystem::RelativePath("Assert/box_specular.png"));
    
    auto boxMaterial = std::make_shared<Material>();
    boxMaterial->setDiffuseTexture(boxTexture);
    boxMaterial->setSpecularTexture(boxSpecularTexture);
    boxMaterial->setShininess(50.0f);

    // create a lot of boxes
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
    std::vector<std::shared_ptr<Object>> boxes;
    for (int i = 0; i < 10; i++) {
        auto box = std::make_shared<Object>();
        box->setMaterial(boxMaterial);
        box->setMesh(MeshFactory::GetBoxMesh());
        glm::mat4 tranalate = glm::translate(glm::mat4(1.0f), cubePositions[i]);
        glm::vec3 rotationRadians = glm::radians(cubePositions[i]);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotationRadians.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, rotationRadians.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, rotationRadians.z, glm::vec3(0.0f, 0.0f, 1.0f));
        box->setTransform(tranalate * rotation);
        boxes.push_back(box);
    }

    // create the light cube
    auto lightShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/Light.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/Light.fs"));
    lightShader->setShaderFunc([shaderPtr = lightShader->shared_from_this()](std::shared_ptr<Camera> camera, 
                                                                            std::shared_ptr<Object> object,
                                                                            std::shared_ptr<RenderEnv> renderEnv){
        shaderPtr->use();
        shaderPtr->setVec3f("color", std::static_pointer_cast<LightMaterial>(object->getMaterial())->getLightColor());
        shaderPtr->setMat4f("model", object->getTransform());
        shaderPtr->setMat4f("view", camera->getViewMatrix());
        shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
    });
    auto materialLight = std::make_shared<LightMaterial>();
    materialLight->setLightColor(glm::vec3(1.0f, 1.0f, 1.0f));


    // set direct light
    auto directLight = std::make_shared<DirectLight>();
    directLight->setMaterial(materialLight);
    directLight->setMesh(MeshFactory::GetBoxMesh());
    directLight->setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    directLight->setDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
    directLight->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 lightScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 lightTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, 30.0f, 30.0f));
    directLight->setTransform(lightTranslate * lightScale);

    renderEnv->setDirectLight(directLight);

    // add point light
    // create a lot of boxes
    glm::vec3 pointLightsPositions[] = {
        glm::vec3( 0.2f,  0.2f,  0.2f),
        glm::vec3( 4.0f,  6.0f, -14.0f),
        glm::vec3(-2.5f, -1.2f, -3.5f),
        glm::vec3(-7.8f, -6.0f, -10.3f),
        glm::vec3( 4.4f, -4.4f, -5.5f)
    };
    for (int i = 0; i < 5; i++) {
        auto pointLight = std::make_shared<PointLight>();
        pointLight->setMaterial(materialLight);
        pointLight->setMesh(MeshFactory::GetBoxMesh());
        pointLight->setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
        pointLight->setDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
        pointLight->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 lightScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        glm::mat4 lightTranslate = glm::translate(glm::mat4(1.0f), pointLightsPositions[i]);
        pointLight->setTransform(lightTranslate * lightScale);

        pointLight->setConstant(1.0f);
        pointLight->setLinear(0.09f);
        pointLight->setQuadratic(0.032f);

        renderEnv->addPointLight(pointLight);
    }

    // add spot light
    // create a lot of boxes
    glm::vec3 spotLightsPositions[] = {
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 5.0f,  0.0f,  0.0f),
        glm::vec3( 0.0f,  0.0f,  -5.0f),
        glm::vec3( -5.0f,  0.0f,  0.0f),
    };
    for (int i = 0; i < 4; i++) {
        auto spotLight = std::make_shared<SpotLight>();
        spotLight->setMaterial(materialLight);
        spotLight->setMesh(MeshFactory::GetBoxMesh());
        spotLight->setAmbient(glm::vec3(0.0f, 0.0f, 0.0f));
        spotLight->setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
        spotLight->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 lightScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        glm::mat4 lightTranslate = glm::translate(glm::mat4(1.0f), spotLightsPositions[i]);
        spotLight->setTransform(lightTranslate * lightScale);

        spotLight->setDirection(glm::vec3(0.0f, 0.0f, 0.0f));
        spotLight->setCutOff(glm::cos(glm::radians(12.5f)));
        spotLight->setOuterCutOff(glm::cos(glm::radians(17.5f)));

        renderEnv->addSpotLight(spotLight);
    }

    // the loop !
    Render::Start(camera, renderEnv);

    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        camera->update(Time::GetDeltaTime());
        for(const auto& box : boxes) {
            Render::Draw(defaultShader, box);
        }
        Render::Draw(lightShader, directLight);

        window.update();
    }
    
     return 0;  
}





