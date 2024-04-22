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
    BaseObject(const std::string& name);
    virtual ~BaseObject() = default;

public:

    template<typename T, typename... Args>
    std::shared_ptr<T> createComponent(Args&&... args)
    {
        static_assert(std::is_base_of<BaseComponent, T>::value, "T must be a derived class of BaseComponent");
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        component->setObject(this);
        mAllComponents[std::type_index(typeid(T))] = component;
        return component;
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
    std::tuple<std::shared_ptr<Components>...> getComponents() {
        return std::make_tuple(getComponent<Components>()...);
    }


    template<typename T>
    bool hasComponent() const {
        return mAllComponents.find(std::type_index(typeid(T))) != mAllComponents.end();
    }

    void update(float deltaTime);

private:
    std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>> mAllComponents;

private:
    Scene* mScene;

};
