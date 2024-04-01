#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
public:
    void use();
    // value settings
public:
    void setBool(const char* variableName, bool value) const;
    void setInt(const char* variableName, int value) const;
    void setFloat(const char* variableName, float value) const;
    void setMat4f(const char* variableName, const glm::mat4& mat4) const;
public:
    unsigned int getShaderProgramID() const { return mShaderProgramID; }
private:
    unsigned int mShaderProgramID;
};