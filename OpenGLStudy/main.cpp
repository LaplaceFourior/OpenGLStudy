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

const char* vertexShaderSource = R"(
    # version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        ourColor = aColor;
        TexCoord = aTexCoord;
    }
)";

const char* fragmentShaderSource = R"(
    # version 330 core

    out vec4 FragColor;

    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D texture1;
    uniform sampler2D texture2;

    void main()
    {
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
        // FragColor = texture(ourTexture, TexCoord);
        // FragColor = vec4(ourColor, 1.0f);
    }
)";

void ProcessInput(GLFWwindow* window, Camera* camera, float deltaTime);

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
    // create the shader
    // vertex
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // compile the shader
    glCompileShader(vertexShader);
    // error check
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // get error message
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // log error message
        std::cout<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED: " << infoLog << std::endl;
    }


    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // compile the shader
    glCompileShader(fragmentShader);
    // error check
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // get error message
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        // log error message
        std::cout<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: " << infoLog << std::endl;
    }
    // for a normal c source file to executable program, we need compile and link, 
    // the same for shader program, after we compile them, we need to link them
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // error check
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if ( !success ) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<< "ERROR::SHADER::PROGRAM::LINKING_FAILED: " << infoLog << std::endl;
    }
    // the vertexShader and the fragmentShader are like source files, after we get the executable program, we do not need
    // the source files anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // a box centered at the origin 
    float boxVertices[] = {
        // position         // color        // texture coordinate
        0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // front 
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
       -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // back
       -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
       -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // left
       -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // up
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // down
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    // every face's index is the same
    unsigned int indices[] = {
        0 , 1 , 2 ,// front
        0 , 2 , 3 ,
        4 , 5 , 6 ,// back
        4 , 6 , 7 ,
        8 , 9 , 10,// left
        8 , 10, 11,
        12, 13, 14,// right
        12, 14, 15,
        16, 17, 18,// up
        16, 18, 19,
        20, 21, 22,// down
        20, 22, 23
    };


    unsigned int VBO1, VAO1, EBO1;
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO1);
    glGenVertexArrays(1, &VAO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


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
    std::string textureLoaction = PROJECT_PATH + std::string( "/Assert/MisterWhite.png");
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

    textureLoaction = PROJECT_PATH + std::string( "/Assert/godot3D.png");
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
    glUseProgram(shaderProgram);
    int textureLocation = glGetUniformLocation(shaderProgram, "texture1"); 
    glUniform1i(textureLocation, 0);
    textureLocation = glGetUniformLocation(shaderProgram, "texture2"); 
    glUniform1i(textureLocation, 1);

    // unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);


    // the loop !
    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    bool firstUpdate = true;
    while (!glfwWindowShouldClose(window)) {

        if( firstUpdate ) {
            lastTime = glfwGetTime();
            firstUpdate = false;
        } else {
            deltaTime = glfwGetTime() - lastTime;
            lastTime = glfwGetTime();
        }
        ProcessInput(window, &camera, deltaTime);
        // set the background color
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // activate the shader program
        glUseProgram(shaderProgram);

        // set the m v p matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.2f, 0.5, 0.8f));// rotate the model by time
        view = camera.getViewMatrix();
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));// set the view position
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

        unsigned int modelLocation = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLocation = glGetUniformLocation(shaderProgram, "view");
        unsigned int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
        glBindVertexArray(VAO1);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // what is swap buffer ?
        glfwSwapBuffers(window);

        // we have to write this, or we will not be able to click on the window
        glfwPollEvents();
    }

    // de-allocate all resources once thy've outlived their purpose
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
    
}


void ProcessInput(GLFWwindow* window, Camera* camera, float deltaTime)
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








