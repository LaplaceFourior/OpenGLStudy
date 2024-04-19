#pragma once
#include <vector>
#include <memory>
#include "Objects/BaseObject.h"
#include <string>
#include "Utils/UUID.h"
#include "Components/IDComponent.h"

class Scene
{
public: 
    Scene() = default;
    virtual ~Scene() = default;

public:
    template<typename T, typename... Args>
    std::shared_ptr<T> createObject(Args&&... args)
    {
        static_assert(std::is_base_of<BaseObject, T>::value, "T must be a derived class of BaseObject");
        auto object = std::make_shared<T>(std::forward<Args>(args)...);
        mAllObjects.push_back(object);
        return object;
    }

    std::shared_ptr<BaseObject> getObject(const UUID& uuid)
    {
        for (auto object : mAllObjects) {
            if (object->getComponent<IDComponent>()->getID() == uuid) {
                return object; 
            }
        }
    }

    template<typename... Components>
    std::vector<std::shared_ptr<BaseObject>> getObjectsWithComponents() {
        std::vector<std::shared_ptr<BaseObject>> results;
        for (auto& object : mAllObjects) {
            if ((object->hasComponent<Components>() && ...)) {
                results.push_back(object);
            }
        }
        return results;
    }

    void update(float deltaTime);

private:
    std::vector<std::shared_ptr<BaseObject>>  mAllObjects;
};