#pragma once

#include <memory>
#include "BaseCamera.hpp"

class DefaultCamera final : public BaseCamera
{
    public:
        DefaultCamera() = default;
        explicit DefaultCamera(std::shared_ptr<BaseCameraImplementation> impl);
        ~DefaultCamera() override = default;

        void accept(std::shared_ptr<BaseVisitor> visitor) override;
};