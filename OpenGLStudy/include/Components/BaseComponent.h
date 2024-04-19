#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BaseObject;

class BaseComponent
{
public:
    BaseComponent() = default;
    virtual ~BaseComponent() = default;
public:
    virtual void update(float deltaTime);
public:
    void setObject(BaseObject* baseObject) { mBaseObject = baseObject; }
protected:
    BaseObject* mBaseObject;
};

