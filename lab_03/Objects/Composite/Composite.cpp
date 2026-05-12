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

Vertex Composite::getCenter() const noexcept
{
    if (m_objects.empty())
        return Vertex(0, 0, 0);

    double sumX = 0, sumY = 0, sumZ = 0;
    for (auto &obj : m_objects)
    {
        auto center = obj->getCenter();
        sumX += center.X();
        sumY += center.Y();
        sumZ += center.Z();
    }
    return Vertex(sumX / m_objects.size(), sumY / m_objects.size(), sumZ / m_objects.size());
}

void Composite::setCenter(const Vertex &point)
{
    auto current = getCenter();
    Vertex offset(point.X() - current.X(), point.Y() - current.Y(), point.Z() - current.Z());
    auto t = Transform::translation(offset);
    transform(t);
}

void Composite::transform(const Transform &transform)
{
    for (auto &obj : m_objects)
        obj->transform(transform);
}
