#pragma once
#include <vector>
#include <memory>
#include "Object.h"

class RenderEnv
{
public:
    RenderEnv() = default;
    ~RenderEnv() = default;
    std::vector<std::shared_ptr<Light>> getLights() { return mLights; }
    void addLight(std::shared_ptr<Light> light) { mLights.push_back(light); }
    float getAmbientStrength() const { return mAmbientStrength; }
    void setAmbientStrength(float ambientStrength) { mAmbientStrength = ambientStrength; }
private:
    std::vector<std::shared_ptr<Light>> mLights;
    float mAmbientStrength;
};