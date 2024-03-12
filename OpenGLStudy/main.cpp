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

    // now we want to draw a quadrangle, we need four vertices and an index
    // first triangle
    float firstTrianglevertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    unsigned int VBO1, VAO1;
    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTrianglevertices), firstTrianglevertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second triangle
    float secondTriangleVertices[] = {
        0.5f, -0.5f, 0.0f,
        0.6f, -0.5f, 0.0f,
        0.55f, 0.0f, 0.0f
    };
    unsigned int VBO2, VAO2;
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices), secondTriangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {

        // set the background color
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // what is swap buffer ?
        glfwSwapBuffers(window);

        // we have to write this, or we will not be able to click on the window
        glfwPollEvents();
    }

    // de-allocate all resources once thy've outlived their purpose
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    
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