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
    void setObject(BaseObject* baseObject) { mBaseObject = baseObject; }
private:
    BaseObject* mBaseObject;
};

