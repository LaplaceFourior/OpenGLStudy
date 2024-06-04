#include "Scene.h"

using namespace TenetEngine;

void Scene::update(float deltaTime)
{
    for (const auto& object : mAllObjects) {
        object->update(deltaTime);
    }
}