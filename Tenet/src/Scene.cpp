#include "Scene.h"

void Scene::update(float deltaTime)
{
    for (const auto& object : mAllObjects) {
        object->update(deltaTime);
    }
}