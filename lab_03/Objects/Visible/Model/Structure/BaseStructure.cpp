#include "BaseStructure.hpp"


BaseStructure::BaseStructure() : m_localCenter(Vertex(0, 0, 0)), m_localTransform(Transform::identity()) { }

Vertex BaseStructure::getLocalCenter() const noexcept
{
    return m_localCenter;
}

Transform BaseStructure::getLocalTransform() const noexcept
{
    return m_localTransform;
}
