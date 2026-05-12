#pragma once

#include <cmath>
#include "BaseCamera.hpp"


class DefaultCamera : public BaseCamera
{
    public:
        DefaultCamera();
        DefaultCamera(const Vertex &position, const Vertex &target);
        virtual ~DefaultCamera() override = default;

        void transform(const Transform &transform) override;
        
        Vertex getCenter() const noexcept override;
        Vertex getPosition() const noexcept override;

        void setCenter(const Vertex &point) override;
        void setPosition(const Vertex &position);
        void setTarget(const Vertex &target);
        
        Transform getViewMatrix() const noexcept override;
        Transform getProjectionMatrix(double aspectRatio) const override;

        void accept(std::shared_ptr<BaseVisitor> visitor) override;

    private:
        Vertex m_position;
        Vertex m_target;
        Vertex m_up;

        Transform lookAt() const noexcept;
        Transform perspective(double fov, double aspect, double near, double far) const;
};