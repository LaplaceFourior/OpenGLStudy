#include "Components/BaseComponent.h"
#include "Entities/BaseEntity.h"

using namespace TenetEngine;

void BaseComponent::update(float deltaTime)
{

}

void BaseComponent::setObject(BaseEntity* BaseEntity)
{
    mBaseEntity = BaseEntity;
}
