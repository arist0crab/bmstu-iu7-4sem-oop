#include "DefaultCamera.hpp"
#include "BaseVisitor.hpp"

DefaultCamera::DefaultCamera(std::shared_ptr<BaseCameraImplementation> impl) : BaseCamera(impl) {}

void DefaultCamera::accept(std::shared_ptr<BaseVisitor> visitor)
{
    if (m_impl)
    {
        visitor->visit(*m_impl);
    }
}