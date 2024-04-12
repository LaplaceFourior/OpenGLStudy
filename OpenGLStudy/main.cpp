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
    renderEnv->setAmbientStrength(0.1f);
    
    // create the shader
    auto defaultShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/default.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/default.fs"));
    
    defaultShader->setShaderFunc([shaderPtr = defaultShader->shared_from_this()](std::shared_ptr<Camera> camera, 
                                                                                std::shared_ptr<Object> object,
                                                                                std::shared_ptr<RenderEnv> renderEnv) {
        // set the background color
        auto textures = object->getMaterial()->getTextures();
        for (auto& texture : textures) {
            texture->bind();
        }
        shaderPtr->use();

        shaderPtr->setBool("useTexture", true);
        shaderPtr->setMat4f("model", object->getTransform());
        shaderPtr->setMat4f("view", camera->getViewMatrix());
        shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
        shaderPtr->setInt("texture1", textures[0]->getTexturePositionID());
        shaderPtr->setInt("texture2", textures[1]->getTexturePositionID());
        shaderPtr->setVec4f("lightColor", renderEnv->getLights()[0]->getLightColor());
        shaderPtr->setVec3f("lightPosition", renderEnv->getLights()[0]->getTranslation());
        shaderPtr->setVec4f("objectColor", object->getMaterial()->getColor());
        shaderPtr->setFloat("ambientStrength", renderEnv->getAmbientStrength());
    });

    auto texture1 = std::make_shared<Texture>(FileSystem::RelativePath("Assert/MisterWhite.png"));
    auto texture2 = std::make_shared<Texture>(FileSystem::RelativePath("Assert/godot3D.png"));
    
    auto materialBox = std::make_shared<Material>();
    materialBox->setColor(glm::vec4(1.0f, 5.0f, 2.0f, 1.0f));
    materialBox->addTexture(texture1);
    materialBox->addTexture(texture2);

    auto boxObject = std::make_shared<Object>();
    boxObject->setMaterial(materialBox);
    boxObject->setMesh(MeshFactory::GetBoxMesh());
    boxObject->setTransform(glm::mat4(1.0f));

    // create the light cube
    auto lightShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/Light.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/Light.fs"));
    lightShader->setShaderFunc([shaderPtr = lightShader->shared_from_this()](std::shared_ptr<Camera> camera, 
                                                                            std::shared_ptr<Object> object,
                                                                            std::shared_ptr<RenderEnv> renderEnv){
        shaderPtr->use();
        shaderPtr->setVec4f("color", object->getMaterial()->getColor());
        shaderPtr->setMat4f("model", object->getTransform());
        shaderPtr->setMat4f("view", camera->getViewMatrix());
        shaderPtr->setMat4f("projection", glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f));
    });
    auto materialLight = std::make_shared<Material>();
    materialLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    auto lightObject = std::make_shared<Light>();
    lightObject->setMaterial(materialLight);
    lightObject->setMesh(MeshFactory::GetBoxMesh());
    lightObject->setLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glm::mat4 lightScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 lightTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    lightObject->setTransform(lightScale * lightTranslate);

    renderEnv->addLight(lightObject);

    // the loop !
    Render::Start(camera, renderEnv);

    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        camera->update(Time::GetDeltaTime());
        Render::Draw(defaultShader, boxObject);
        Render::Draw(lightShader, lightObject);

        window.update();
    }
    
     return 0;  
}





