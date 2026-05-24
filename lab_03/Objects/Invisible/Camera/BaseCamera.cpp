#include "BaseCamera.hpp"

BaseCamera::BaseCamera(std::shared_ptr<BaseCameraImplementation> impl) : m_impl(impl) {}

std::shared_ptr<BaseCameraImplementation> BaseCamera::getImplementation() const
{
    return m_impl;
}