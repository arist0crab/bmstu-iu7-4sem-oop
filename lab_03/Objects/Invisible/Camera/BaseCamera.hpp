#pragma once

#include <memory>
#include "InvisibleObject.hpp"
#include "Transform.hpp"
#include "Vertex.hpp"

class BaseCamera : public InvisibleObject
{
    public:
        BaseCamera() = default;
        virtual ~BaseCamera() override = default;

        virtual void transform(const Transform &transform) = 0;
        virtual Vertex getPosition() const noexcept = 0;
        virtual Transform getViewMatrix() const noexcept = 0;
        virtual Transform getProjectionMatrix(double aspectRatio) const = 0;
};