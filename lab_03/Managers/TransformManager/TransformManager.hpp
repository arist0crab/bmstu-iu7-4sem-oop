#pragma once

#include <iostream>
#include "BaseManager.hpp"
#include "SceneManager.hpp"
#include "ManagerSolution.hpp"
#include "Transform.hpp"


class TransformManager : public BaseManager
{
    public:
        TransformManager() = default;
        virtual ~TransformManager() override = default;

        void moveObject(size_t id, double dx, double dy, double dz);
        void scaleObject(size_t id, double kx, double ky, double kz);
        void rotateObject(size_t id, double ax, double ay, double az);
};