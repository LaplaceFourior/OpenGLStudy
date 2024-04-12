#include "Shader.h"
#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
    load(vertexFilePath, fragmentFilePath);
}

void Shader::load(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // make sure that ifstream objects can throw exceptions
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexFilePath);
        fShaderFile.open(fragmentFilePath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cout<< "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    // vertex
    const char* vCode = vertexCode.c_str();
    const char* fCode = fragmentCode.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vCode, NULL);
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
    glShaderSource(fragmentShader, 1, &fCode, NULL);
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
    mShaderProgramID = glCreateProgram();
    glAttachShader(mShaderProgramID, vertexShader);
    glAttachShader(mShaderProgramID, fragmentShader);
    glLinkProgram(mShaderProgramID);
    // error check
    glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &success);
    if ( !success ) {
        glGetProgramInfoLog(mShaderProgramID, 512, NULL, infoLog);
        std::cout<< "ERROR::SHADER::PROGRAM::LINKING_FAILED: " << infoLog << std::endl;
    }
    // the vertexShader and the fragmentShader are like source files, after we get the executable program, we do not need
    // the source files anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() 
{
    glUseProgram(mShaderProgramID);
}

void Shader::setBool(const char* variableName, bool value) const
{
    glUniform1i(glGetUniformLocation(mShaderProgramID, variableName), (int)value);
}

void Shader::setInt(const char* variableName, int value) const
{
    glUniform1i(glGetUniformLocation(mShaderProgramID, variableName), value);
}

void Shader::setFloat(const char* variableName, float value) const
{
    glUniform1f(glGetUniformLocation(mShaderProgramID, variableName), value);
}
void Shader::setMat4f(const char* variableName, const glm::mat4& mat4) const
{
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgramID, variableName), 1, GL_FALSE, glm::value_ptr(mat4));
}
void Shader::setVec3f(const char* variableName, const glm::vec3& vec3) const
{
    glUniform3f(glGetUniformLocation(mShaderProgramID, variableName), vec3.x, vec3.y, vec3.z);
}
void Shader::applyShaderFunc(std::shared_ptr<Camera> camera, std::shared_ptr<Object> object)
{
    if (shaderFunc) {
        shaderFunc(camera, object);
    }
}

