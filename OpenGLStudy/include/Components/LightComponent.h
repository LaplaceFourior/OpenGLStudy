#pragma once

#include "BaseComponent.h"

class LightComponent : public BaseComponent
{
    ACLASS(LightComponent, BaseComponent)
public:
    LightComponent() = default;
    ~LightComponent() = default;
public:
    const glm::vec3& getAmbient() const { return mAmbient; }
    const glm::vec3& getDiffuse() const { return mDiffuse; }
    const glm::vec3& getSpecular() const { return mSpecular; }

    void setAmbient(const glm::vec3& ambient) { mAmbient = ambient; }
    void setDiffuse(const glm::vec3& diffuse) { mDiffuse = diffuse; }
    void setSpecular(const glm::vec3& specular) { mSpecular = specular; }
    void update(float deltaTime) override;
private:
    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;
}; 


class DirectLightComponent : public LightComponent
{
    ACLASS(DirectLightComponent, LightComponent)
public:
    DirectLightComponent() = default;
    ~DirectLightComponent() = default;
public:
    void setDirection(const glm::vec3& direction) { mDirection = direction; }
    const glm::vec3& getDirection() const { return mDirection; }
    void update(float deltaTime) override;
private:
    glm::vec3 mDirection;
};

class PointLightComponent : public LightComponent
{
    ACLASS(PointLightComponent, LightComponent)
public:
    PointLightComponent() = default;
    ~PointLightComponent() = default;
public:
    float getConstant() const { return mConstant; }
    void setConstant(float constant) { mConstant = constant; }

    float getLinear() const { return mLinear; }
    void setLinear(float linear) { mLinear = linear; }

    float getQuadratic() const { return mQuadratic; }
    void setQuadratic(float quadratic) { mQuadratic = quadratic; }

    const glm::vec3& getPosition() const { return mPosition; }

    void update(float deltaTime) override;
private:
    glm::vec3 mPosition;
    float mConstant;
    float mLinear;
    float mQuadratic;
};

class SpotLightComponent : public LightComponent
{
    ACLASS(SpotLightComponent, LightComponent)
public:
    SpotLightComponent() = default;
    ~SpotLightComponent() = default;
public:
    const glm::vec3& getDirection() const { return direction; }
    void setDirection(const glm::vec3& dir) { direction = dir; }

    float getCutOff() const { return mCutOff; }
    void setCutOff(float cutoff) { mCutOff = cutoff; }

    float getOuterCutOff() const { return mOuterCutOff; }
    void setOuterCutOff(float outerCutOff) { mOuterCutOff = outerCutOff; }

    const glm::vec3& getPosition() const { return mPosition; }
    void setPosition(const glm::vec3& position) { mPosition = position; }

    void update(float deltaTime) override;
protected:
    glm::vec3 mPosition;
    glm::vec3 direction;
    float mCutOff;
    float mOuterCutOff;
};


