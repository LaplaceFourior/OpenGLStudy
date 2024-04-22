#include "Components/BaseComponent.h"
#include "Objects/BaseObject.h"

void BaseComponent::update(float deltaTime)
{

}

void BaseComponent::setObject(BaseObject* baseObject)
{
    mBaseObject = baseObject;
}
