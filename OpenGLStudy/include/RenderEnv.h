// #pragma once
// #include <vector>
// #include <memory>
// #include "Object.h"

// class RenderEnv
// {
// public:
//     RenderEnv() = default;
//     ~RenderEnv() = default;
//     std::shared_ptr<Light> getAllDirectLight() { return mDirectLight; }
//     std::vector<std::shared_ptr<PointLight>> getAllPointLights() { return mPointLights; }
//     std::vector<std::shared_ptr<SpotLight>> getAllSpotLights() { return mSpotLights; }

//     void addPointLight(std::shared_ptr<PointLight> light) { mPointLights.push_back(light); }
//     void addSpotLight(std::shared_ptr<SpotLight> light) { mSpotLights.push_back(light); }
//     void setDirectLight(std::shared_ptr<DirectLight> light) { mDirectLight = light; }
// private:
//     std::shared_ptr<DirectLight> mDirectLight;
//     std::vector<std::shared_ptr<PointLight>> mPointLights;
//     std::vector<std::shared_ptr<SpotLight>> mSpotLights;
// };