#include "BaseObject.hpp"


Vertex BaseObject::getCenter() const noexcept 
{ 
    return m_center; 
}

void BaseObject::setCenter(const Vertex &center) noexcept 
{ 
    m_center = center; 
}

void BaseObject::add(std::shared_ptr<BaseObject> object) { }

void BaseObject::remove(const size_t id) noexcept { }