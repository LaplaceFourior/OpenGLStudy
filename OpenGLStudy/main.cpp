#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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
#include <memory>

void ProcessInputKey(GLFWwindow* window, Camera* camera, float deltaTime);
void ProcessInputMouse(GLFWwindow* window, Camera* camera, double& lastX, double& lastY, bool& firstMouse);

int main() 
{
    // no error check, just realize it!

    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "finish a scene by myself", NULL, NULL);
    //error check
    if (window == NULL) {
        // log error message
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    } 
    glfwMakeContextCurrent(window);
    
    // capture mouse input
    // why process mouse here? out the loop ? how to combine mouse process and keyboard process ?
    Input::Init(window);
    //error check
    // glad: load all opengl functions' pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // log error message
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // camera settings
    Camera camera;
    camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.setLookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));

    // about the opengl
    // enable depth test to create 3D graph
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // create the shader
    Shader defaultShader = Shader(FileSystem::RelativePath("Assert/Shaders/default.vs"), 
                                    FileSystem::RelativePath("Assert/Shaders/default.fs"));

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

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// x
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    // flip the image
    stbi_set_flip_vertically_on_load(true);
    std::string textureLoaction = FileSystem::RelativePath("Assert/MisterWhite.png");
    unsigned char* data = stbi_load(textureLoaction.c_str(), &width, &height, &nrChannels, 0);
    if( data ) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// x
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    textureLoaction = FileSystem::RelativePath("Assert/godot3D.png");
    data = stbi_load(textureLoaction.c_str(), &width, &height, &nrChannels, 0);
    if( data ) {
        // attention! some picture has no A only RGB but not RGBA, glTexImage2D with GL_RGB or GL_RGBA may cause error
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // set the texture
    defaultShader.use();
    defaultShader.setInt("texture1", 0);
    defaultShader.setInt("texture2", 1);

    // unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

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
    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    bool firstUpdate = true;
    double lastX = 400, lastY = 300;
    bool firstMouse = true;
    while (!glfwWindowShouldClose(window)) {

        if( firstUpdate ) {
            lastTime = glfwGetTime();
            firstUpdate = false;
        } else {
            deltaTime = glfwGetTime() - lastTime;
            lastTime = glfwGetTime();
        }
        ProcessInputKey(window, &camera, deltaTime);
        ProcessInputMouse(window, &camera, lastX, lastY, firstMouse);
        // set the background color
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
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

        defaultShader.setMat4f("model", model);
        defaultShader.setMat4f("view", view);
        defaultShader.setMat4f("projection", projection);

        mesh.draw();

        TextRender2D::RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        TextRender2D::RenderText("(C) LearnOpenGL.com", 25.0f, 25.0f, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));

        panelOne.draw(model, view, projection);
        // what is swap buffer ?
        glfwSwapBuffers(window);

        // we have to write this, or we will not be able to click on the window
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
    
}


void ProcessInputKey(GLFWwindow* window, Camera* camera, float deltaTime)
{
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ){
        // quit
        glfwSetWindowShouldClose(window, true);
    }

    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ) {
        camera->move(Direction::FORWARD, deltaTime);
    }

    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ) {
        camera->move(Direction::BACKWARD, deltaTime);
    }

    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ) {
        camera->move(Direction::LEFT, deltaTime);
    }

    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ) {
        camera->move(Direction::RIGHT, deltaTime);
    }

}

void ProcessInputMouse(GLFWwindow* window, Camera* camera, double& lastX, double& lastY, bool& firstMouse)
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    if (firstMouse) 
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = - (float)(xPos - lastX);
    float yOffset = - (float)(yPos - lastY); 

    lastX = xPos;
    lastY = yPos;

    camera->turnAround(xOffset, yOffset);
}






