#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <memory>

#include "Components/LightComponent.h"
#include "Material.h"

using ShaderFunc = std::function<void(
        std::shared_ptr<Material> material,
        std::vector<std::shared_ptr<DirectLightComponent>> directLights,
        std::vector<std::shared_ptr<PointLightComponent>> pointLights,
        std::vector<std::shared_ptr<SpotLightComponent>> spotLights,
        const glm::vec3& cameraPosition,
        const glm::mat4& cameraTransform,
        const glm::mat4& modelTransform)>;

class Shader : public std::enable_shared_from_this<Shader>
{
public:
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    Shader() = default;
public:
    void load(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    void use();
    // value settings
public:
    void setBool(const char* variableName, bool value) const;
    void setInt(const char* variableName, int value) const;
    void setFloat(const char* variableName, float value) const;
    void setMat4f(const char* variableName, const glm::mat4& mat4) const;
    void setVec3f(const char* variableName, const glm::vec3& vec3) const;
    void setVec4f(const char* variableName, const glm::vec4& vec4) const;
public:
    unsigned int getShaderProgramID() const { return mShaderProgramID; }
private:
    unsigned int mShaderProgramID;
public:
    void setShaderFunc(ShaderFunc func) { shaderFunc = func;}
    void applyShaderFunc(std::shared_ptr<Material> material,
        std::vector<std::shared_ptr<DirectLightComponent>> directLights,
        std::vector<std::shared_ptr<PointLightComponent>> pointLights,
        std::vector<std::shared_ptr<SpotLightComponent>> spotLights,
        const glm::vec3& cameraPosition,
        const glm::mat4& cameraTransform,
        const glm::mat4& modelTransform);
private:
    ShaderFunc shaderFunc;
};