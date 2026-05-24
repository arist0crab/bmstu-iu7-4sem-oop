#pragma once

#include <memory>
#include "InvisibleObject.hpp"
#include "BaseCameraImplementation.hpp"

class BaseCamera : public InvisibleObject
{
    public:
        BaseCamera() = default;
        explicit BaseCamera(std::shared_ptr<BaseCameraImplementation> impl);
        ~BaseCamera() override = default;

        std::shared_ptr<BaseCameraImplementation> getImplementation() const;

    protected:
        std::shared_ptr<BaseCameraImplementation> m_impl;
};