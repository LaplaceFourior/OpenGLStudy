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

int main() 
{

    Window window(800, 600, "finish a scene by myself");
    window.enableDepthTest(true);
    window.setMouseVisible(false);
    window.setBackgroundColor(glm::vec4(0.2f, 0.5f, 0.6f, 1.0f));

    // capture mouse input
    // why process mouse here? out the loop ? how to combine mouse process and keyboard process ?
    Input::Init(&window);
    Time::Init();
    // camera settings
    Camera camera;
    camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.setLookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));

    
    // create the shader
    Shader defaultShader (FileSystem::RelativePath("Assert/Shaders/default.vs"), 
                            FileSystem::RelativePath("Assert/Shaders/default.fs"));
    Texture texture1(FileSystem::RelativePath("Assert/MisterWhite.png"));
    Texture texture2(FileSystem::RelativePath("Assert/godot3D.png"));
    // a box centered at the origin 
    std::vector<Vertex> boxVertices = {
        // position         // color        // texture coordinate
       {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // front 
       {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
       {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
       {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // back
       {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
       {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
       {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // left
       {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
       {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
       {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // right
       {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
       {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
       {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // up
       {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
       {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
       {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // down
       {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
       {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
    };
    // every face's index is the same
    std::vector<TriangleIndex> boxTriangleIndices = {
        {0 , 1 , 2 },// front
        {0 , 2 , 3 },
        {4 , 5 , 6 },// back
        {4 , 6 , 7 },
        {8 , 9 , 10},// left
        {8 , 10, 11},
        {12, 13, 14},// right
        {12, 14, 15},
        {16, 17, 18},// up
        {16, 18, 19},
        {20, 21, 22},// down
        {20, 22, 23}
    };

    Mesh mesh(boxVertices, boxTriangleIndices);

    // font init
    Shader text2DShader = Shader(FileSystem::RelativePath("Assert/Shaders/text.vs"), 
                                    FileSystem::RelativePath("Assert/Shaders/text.fs"));
    TextRender2D::Init(
        FileSystem::RelativePath("Assert/Shaders/text.vs"), 
        FileSystem::RelativePath("Assert/Shaders/text.fs"),
        800,
        600);
    TextRender2D::LoadFonts(FileSystem::RelativePath("Assert/Fonts/arial.ttf"));   

    // create 2Dpanel in 3D space !
    std::shared_ptr<Shader> text2Din3DShader = std::make_shared<Shader>(FileSystem::RelativePath("Assert/Shaders/text2Din3D.vs"), 
                                                                        FileSystem::RelativePath("Assert/Shaders/text2Din3D.fs"));
    Panel::Init();
    Panel::LoadFonts(FileSystem::RelativePath("Assert/Fonts/arial.ttf"));
    Panel panelOne(text2Din3DShader, "Hello world", glm::vec3(1.0f, 0.0f, 0.0f));
    
    // the loop !
    while (!window.shouldClose()) {
        Time::Update();
        window.clearCache();
        camera.update(Time::GetDeltaTime());
        // set the background color
        texture1.bind();
        texture2.bind();
        // activate the shader program
        defaultShader.use();
        // set the m v p matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.2f, 0.5, 0.8f));// rotate the model by time
        view = camera.getViewMatrix();
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));// set the view position
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        // projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 100.0f);
        defaultShader.setMat4f("model", model);
        defaultShader.setMat4f("view", view);
        defaultShader.setMat4f("projection", projection);
        defaultShader.setInt("texture1", texture1.getTexturePositionID());
        defaultShader.setInt("texture2", texture2.getTexturePositionID());
        
        mesh.draw();

        window.update();
    }
    
     return 0;  
}





