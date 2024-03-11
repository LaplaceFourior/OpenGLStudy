#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const char* vertexShaderSource = R"(
    # version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    # version 330 core

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)";

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
    
    //error check
    // glad: load all opengl functions' pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // log error message
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // about the opengl things

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

    //we want to draw a triangle on the screen, so we first need to indicate the vertex of a triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    // we need to allocate some sapce for storing the triangle data
    unsigned int VBO, VAO;
    // allocate the space
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // indicate the type of the data we're going to store
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // indicate how we store the data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // indicate how we explain each data
    // the first parameter is 0 which means that the data we store here is for the parameter in vertex shader which 
    // is decorated with layout (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // enable the vertex attribute 0 which is the first parameter in glVertexAttribPointer and
    // decorated with layout (location = 0) in vertex shader
    glEnableVertexAttribArray(0);



    // we completed a set of VAO and VBO configuration, in one draw loop, we can set the different set of VAO and VBO 
    // to draw different things, so we unbind them first and decide which set of VAO and VBO we use in each draw loop
    // `unbind` is so called, to realize it, we just need to bind it to a None VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {

        // set the background color
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use which shader? 
        glUseProgram(shaderProgram);
        // we do not need to bind the buffer, only need to bind the VAO,  because emm..... maybe when we bind the VAO, the VAO
        // indirectly binds the VBO already ? ? ?, maybe I will never know the internal things 
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindVertexArray(VAO);
        // the second parameter indicates the start index of the vertex array
        // the last parameter indicates how many vertices we are going to draw
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // what is swap buffer ?
        glfwSwapBuffers(window);

        // we have to write this, or we will not be able to click on the window
        glfwPollEvents();
    }

    // de-allocate all resources once thy've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
    
}

/**
 * data         author          description
 * 20240311     LaplaceFourior  add error check
 * 
 * 
*/