#pragma once
#include <memory>
// #include <vector>
#include <unordered_map>
#include <typeindex>
#include "Components/BaseComponent.h"
#include <string>
#include "Object.h"

class Scene;

class BaseEntity : public Object
{
    ACLASS(BaseEntity, Object)
public:
    BaseEntity(const std::string& name);
    virtual ~BaseEntity() = default;

public:

    template<typename T, typename... Args>
    std::shared_ptr<T> createComponent(Args&&... args)
    {
        static_assert(std::is_base_of<BaseComponent, T>::value, "T must be a derived class of BaseComponent");
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        component->setObject(this);
        mAllComponents[T::getClassStatic()] = component;
        return component;
    }

    template<typename T>
    std::shared_ptr<T> getComponent()
    {
        static_assert(std::is_base_of<BaseComponent, T>::value, "T must be a derived class of BaseComponent");
        for (auto it = mAllComponents.begin(); it != mAllComponents.end(); it++) {
            if (::ClassDB::isClass(it->first, T::getClassStatic())) {
                return std::static_pointer_cast<T>(it->second);
            }
        }
        return nullptr;
    }

    template<typename... Components>
    std::tuple<std::shared_ptr<Components>...> getComponents() {
        return std::make_tuple(getComponent<Components>()...);
    }


    template<typename T>
    bool hasComponent() const {
        for (auto it = mAllComponents.begin(); it != mAllComponents.end(); it++) {
            if (::ClassDB::isClass(it->first, T::getClassStatic())) {
                return true;
            }
        }
        return false;
    }

    void update(float deltaTime);

private:
    std::unordered_map<std::string, std::shared_ptr<BaseComponent>> mAllComponents;

private:
    Scene* mScene;

};
