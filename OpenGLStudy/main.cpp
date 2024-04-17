#include <iostream>
#include <math.h>
#include <memory>

#include <string.h>

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
        
        shaderPtr->setVec3f("light.position", renderEnv->getLights()[0]->getTranslation());
        shaderPtr->setVec3f("light.ambient", renderEnv->getLights()[0]->getAmbient());
        shaderPtr->setVec3f("light.diffuse", renderEnv->getLights()[0]->getDiffuse());
        shaderPtr->setVec3f("light.specular", renderEnv->getLights()[0]->getSpecular());

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

    auto lightObject = std::make_shared<Light>();
    lightObject->setMaterial(materialLight);
    lightObject->setMesh(MeshFactory::GetBoxMesh());
    lightObject->setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    lightObject->setDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
    lightObject->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 lightScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 lightTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f));
    lightObject->setTransform(lightScale * lightTranslate);

    renderEnv->addLight(lightObject);

    // the loop !
    Render::Start(camera, renderEnv);

    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        camera->update(Time::GetDeltaTime());
        for(const auto& box : boxes) {
            Render::Draw(defaultShader, box);
        }
        Render::Draw(lightShader, lightObject);

        window.update();
    }
    
     return 0;  
}





