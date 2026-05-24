#pragma once

#include "Transform.hpp"
#include "Vertex.hpp"

class BaseCameraImplementation
{
    public:
        BaseCameraImplementation() = default;
        virtual ~BaseCameraImplementation() = default;

        virtual void transform(const Transform &transform) = 0;
        virtual Vertex getPosition() const noexcept = 0;
        virtual Transform getViewMatrix() const noexcept = 0;
        virtual Transform getProjectionMatrix(double aspectRatio) const = 0;
};