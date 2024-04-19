#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>
#include "Components/BaseComponent.h"
#include <string>

class Scene;

class BaseObject
{
public:
    BaseObject() = delete;
    virtual ~BaseObject() = default;

public:

    template<typename T>
    void addComponent(std::shared_ptr<T> component)
    {
        mAllComponents[std::type_index(typeid(T))] = component;
    }

    template<typename T>
    std::shared_ptr<T> getComponent()
    {
        static_assert(std::is_base_of<BaseComponent, T>::value, "T must be a derived class of BaseComponent");
        auto it = mAllComponents.find(std::type_index(typeid(T)));
        if (it != mAllComponents.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template<typename... Components>
    std::tuple<std::shared_ptr<Components>...> getComponents() const {
        return std::make_tuple(getComponent<Components>()...);
    }


    template<typename T>
    bool hasComponent() const {
        return mAllComponents.find(std::type_index(typeid(T))) != mAllComponents.end();
    }

public:
    std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>> mAllComponents;

private:
    std::shared_ptr<Scene> m_object;

};



// class Light : public Object
// {
// public:
//     void setAmbient(const glm::vec3& ambient) { mAmbient = ambient; }
//     void setDiffuse(const glm::vec3& diffuse) { mDiffuse = diffuse; }
//     void setSpecular(const glm::vec3& specular) { mSpecular = specular; }

//     const glm::vec3& getAmbient() const { return mAmbient; }
//     const glm::vec3& getDiffuse() const { return mDiffuse; }
//     const glm::vec3& getSpecular() const { return mSpecular; }
// private:
//     glm::vec3 mAmbient;
//     glm::vec3 mDiffuse;
//     glm::vec3 mSpecular;
// };

// class DirectLight : public Light
// {
// };

// class PointLight : public Light 
// {
// public:
//     float getConstant() const { return mConstant; }
//     void setConstant(float constant) { mConstant = constant; }

//     float getLinear() const { return mLinear; }
//     void setLinear(float linear) { mLinear = linear; }

//     float getQuadratic() const { return mQuadratic; }
//     void setQuadratic(float quadratic) { mQuadratic = quadratic; }

// private:
//     float mConstant;
//     float mLinear;
//     float mQuadratic;
// };

// class SpotLight : public Light 
// {
// public:
//     const glm::vec3& getDirection() const { return direction; }
//     void setDirection(const glm::vec3& dir) { direction = dir; }

//     float getCutOff() const { return cutOff; }
//     void setCutOff(float cutoff) { cutOff = cutoff; }

//     float getOuterCutOff() const { return outerCutOff; }
//     void setOuterCutOff(float outerCutOff) { outerCutOff = outerCutOff; }

// private:
//     glm::vec3 direction;
//     float cutOff;
//     float outerCutOff;
// };