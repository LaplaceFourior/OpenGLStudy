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

    
    // create the shader
    auto defaultShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/default.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/default.fs"));
    
    defaultShader->setShaderFunc([shaderPtr = defaultShader->shared_from_this()](std::shared_ptr<Camera> camera, std::shared_ptr<Object> object) {
        // set the background color
        auto textures = object->getMaterial()->getTextures();
        for (auto& texture : textures) {
            texture->bind();
        }
        shaderPtr->use();
        // set the m v p matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.2f, 0.5, 0.8f));// rotate the model by time
        view = camera->getViewMatrix();
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));// set the view position
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGH, 0.1f, 100.0f);
        // projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 100.0f);
        shaderPtr->setBool("useTexture", true);
        shaderPtr->setMat4f("model", model);
        shaderPtr->setMat4f("view", view);
        shaderPtr->setMat4f("projection", projection);
        shaderPtr->setInt("texture1", textures[0]->getTexturePositionID());
        shaderPtr->setInt("texture2", textures[1]->getTexturePositionID());
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

    // the loop !
    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        camera->update(Time::GetDeltaTime());
        Render::Start(camera);
        Render::Draw(defaultShader, boxObject);

        window.update();
    }
    
     return 0;  
}





