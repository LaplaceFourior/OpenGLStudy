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
    void setActive(bool active) { bActive = active; }
    bool isActive() const { return bActive; }
public:
    virtual void update(float deltaTime);
public:
    void setObject(BaseObject* baseObject);
protected:
    BaseObject* mBaseObject;
private:
    bool bActive = true;
};

