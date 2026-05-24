#pragma once

#include <cmath>
#include "BaseCameraImplementation.hpp"

class DefaultCameraImplementation : public BaseCameraImplementation
{
    public:
        DefaultCameraImplementation();
        DefaultCameraImplementation(const Vertex &position, const Vertex &target);
        ~DefaultCameraImplementation() override = default;

        void transform(const Transform &transform) override;
        Vertex getPosition() const noexcept override;
        Transform getViewMatrix() const noexcept override;
        Transform getProjectionMatrix(double aspectRatio) const override;

    private:
        Vertex m_position;
        Vertex m_target;
        Vertex m_up;

        Transform lookAt() const noexcept;
        Transform perspective(double fov, double aspect, double near, double far) const;
};