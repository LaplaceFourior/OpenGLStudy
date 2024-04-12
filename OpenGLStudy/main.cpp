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

enum RenderThreadMode {
	RENDER_THREAD_UNSAFE,
	RENDER_THREAD_SAFE,
	RENDER_SEPARATE_THREAD
};

int main() 
{

    Window window(800, 600, "finish a scene by myself");
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
    auto texture1 = std::make_shared<Texture>(FileSystem::RelativePath("Assert/MisterWhite.png"));
    auto texture2 = std::make_shared<Texture>(FileSystem::RelativePath("Assert/godot3D.png"));
    
    auto materialBox = std::make_shared<Material>();

    materialBox->setColor(glm::vec4(1.0f, 5.0f, 2.0f, 1.0f));
    materialBox->addTexture(texture1);
    materialBox->addTexture(texture2);

    auto boxObject = std::make_shared<Object>(defaultShader, MeshFactory::GetBoxMesh(), materialBox);

    // the loop !
    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        camera->update(Time::GetDeltaTime());
        Render::Start(camera);
        Render::Draw(boxObject);

        window.update();
    }
    
     return 0;  
}





