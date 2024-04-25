#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"

class BaseEntity;

class BaseComponent : public Object
{
    ACLASS(BaseComponent, Object)
public:
    BaseComponent() = default;
    virtual ~BaseComponent() = default;
    void setActive(bool active) { bActive = active; }
    bool isActive() const { return bActive; }
public:
    virtual void update(float deltaTime);
public:
    void setObject(BaseEntity* BaseEntity);
protected:
    BaseEntity* mBaseEntity;
private:
    bool bActive = true;
};

// #define ACOMPONENT(mClass, mInherit, bUnique)\
//     ACLASS(mClass, mInherit)\
// protected:\
//     bool mUnique = bUnique;\
// private:
