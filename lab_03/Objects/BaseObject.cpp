#include "BaseObject.hpp"

std::shared_ptr<BaseObject> BaseObject::getObject(const size_t id) const
{
    (void)id;
    return nullptr;
}

void BaseObject::add(std::shared_ptr<BaseObject> object) { }

void BaseObject::remove(const size_t id) noexcept { }