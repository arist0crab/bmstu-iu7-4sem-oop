#include "Composite.hpp"


std::shared_ptr<BaseObject> Composite::getObject(const size_t id) const
{
    if (id < m_objects.size())
        return m_objects[id];
    return nullptr;
}

void Composite::add(std::shared_ptr<BaseObject> object)
{
    m_objects.push_back(object);
}

void Composite::remove(const size_t id) noexcept
{
    if (id < m_objects.size())
        m_objects.erase(m_objects.begin() + id);
}

void Composite::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto &obj : m_objects)
        obj->accept(visitor);
}