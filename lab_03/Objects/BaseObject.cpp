#include "BaseObject.hpp"

std::shared_ptr<BaseObject> BaseObject::getObject(const size_t id) const
{
    // TODO реализовать
    return nullptr;
}

void BaseObject::setLocalCenter(const Vertex &point)
{
    m_localCenter = point;
    // TODO логика пересчета координат
}

void BaseObject::setLocalTransform(const Transform &transform)
{
    m_localTransform = transform;
}

Vertex BaseObject::getLocalCenter() const noexcept
{
    return m_localCenter;
}

Transform BaseObject::getLocalTransform() const noexcept
{
    return m_localTransform;
}
