#pragma once

class BaseObject;

class BaseComponent
{
    friend class Scene;
protected:
    BaseComponent() = default;
    virtual ~BaseComponent() = default;
private:
    std::shared_ptr<BaseObject> m_object;
};

