#pragma once

#include <memory>
#include "BaseManager.hpp"
#include "BaseObject.hpp"
#include "Vertex.hpp"
#include "Transform.hpp"


class TransformManager : public BaseManager
{
    public:
        TransformManager() = default;
        virtual ~TransformManager() override = default;

        void moveObject(std::shared_ptr<BaseObject> object, double dx, double dy, double dz);
        void scaleObject(std::shared_ptr<BaseObject> object, double kx, double ky, double kz);
        void rotateObject(std::shared_ptr<BaseObject> object, double ax, double ay, double az);
};