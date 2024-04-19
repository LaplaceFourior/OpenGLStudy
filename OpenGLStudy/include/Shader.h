// #pragma once

// #include <string>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <functional>
// #include <memory>
// #include "Camera.h"
// #include "Object.h"
// #include "RenderEnv.h"

// using ShaderFunc = std::function<void(std::shared_ptr<Camera>, std::shared_ptr<Object>, std::shared_ptr<RenderEnv>)>;

// class Shader : public std::enable_shared_from_this<Shader>
// {
// public:
//     Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
//     Shader() = default;
// public:
//     void load(const std::string& vertexFilePath, const std::string& fragmentFilePath);
//     void use();
//     // value settings
// public:
//     void setBool(const char* variableName, bool value) const;
//     void setInt(const char* variableName, int value) const;
//     void setFloat(const char* variableName, float value) const;
//     void setMat4f(const char* variableName, const glm::mat4& mat4) const;
//     void setVec3f(const char* variableName, const glm::vec3& vec3) const;
//     void setVec4f(const char* variableName, const glm::vec4& vec4) const;
// public:
//     unsigned int getShaderProgramID() const { return mShaderProgramID; }
// private:
//     unsigned int mShaderProgramID;
// public:
//     void setShaderFunc(ShaderFunc func) { shaderFunc = func;}
//     void applyShaderFunc(std::shared_ptr<Camera>, std::shared_ptr<Object>, std::shared_ptr<RenderEnv>);
// private:
//     ShaderFunc shaderFunc;
// };