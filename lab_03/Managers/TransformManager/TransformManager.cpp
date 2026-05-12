#include "TransformManager.hpp"


void TransformManager::moveObject(std::shared_ptr<BaseObject> object, double dx, double dy, double dz)
{
    auto transform = Transform::translation(dx, dy, dz);
    object->transform(transform);
}

void TransformManager::scaleObject(std::shared_ptr<BaseObject> object, double kx, double ky, double kz)
{
    auto transform = Transform::scale(kx, ky, kz);
    object->transform(transform);
}

void TransformManager::rotateObject(std::shared_ptr<BaseObject> object, double ax, double ay, double az)
{
    auto transform = Transform::rotate(ax, ay, az);
    object->transform(transform);
}