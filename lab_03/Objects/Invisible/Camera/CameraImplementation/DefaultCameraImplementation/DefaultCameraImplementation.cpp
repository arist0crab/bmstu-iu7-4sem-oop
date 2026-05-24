#include "DefaultCameraImplementation.hpp"

DefaultCameraImplementation::DefaultCameraImplementation() : m_position(0, 0, 10), m_target(0, 0, 0), m_up(0, 1, 0) {}

DefaultCameraImplementation::DefaultCameraImplementation(const Vertex &position, const Vertex &target) : m_position(position), m_target(target), m_up(0, 1, 0) {}

void DefaultCameraImplementation::transform(const Transform &transform)
{
    m_position.transform(transform);
    m_target.transform(transform);

    Vertex zero(0, 0, 0);
    Vertex upPoint(m_up.X(), m_up.Y(), m_up.Z());

    zero.transform(transform);
    upPoint.transform(transform);

    m_up = (upPoint - zero).normalize();
}

Vertex DefaultCameraImplementation::getPosition() const noexcept 
{ 
    return m_position; 
}

Transform DefaultCameraImplementation::getViewMatrix() const noexcept
{
    return lookAt();
}

Transform DefaultCameraImplementation::getProjectionMatrix(double aspectRatio) const
{
    return perspective(60.0, aspectRatio, 0.1, 100.0);
}

Transform DefaultCameraImplementation::lookAt() const noexcept
{
    Vertex forward = (m_target - m_position).normalize();
    Vertex right = forward.cross(m_up).normalize();
    Vertex up = right.cross(forward);

    Transform view = Transform::identity();
    view(0, 0) = right.X();   view(0, 1) = up.X();   view(0, 2) = -forward.X();   view(0, 3) = 0;
    view(1, 0) = right.Y();   view(1, 1) = up.Y();   view(1, 2) = -forward.Y();   view(1, 3) = 0;
    view(2, 0) = right.Z();   view(2, 1) = up.Z();   view(2, 2) = -forward.Z();   view(2, 3) = 0;
    view(3, 0) = -right.dot(m_position);  view(3, 1) = -up.dot(m_position);  view(3, 2) = forward.dot(m_position);  view(3, 3) = 1;

    return view;
}

Transform DefaultCameraImplementation::perspective(double fov, double aspect, double near, double far) const
{
    double f = 1.0 / std::tan(fov * M_PI / 360.0);
    double rangeInv = 1.0 / (near - far);

    Transform proj = Transform::zero();
    proj(0, 0) = f / aspect;
    proj(1, 1) = f;
    proj(2, 2) = (near + far) * rangeInv;
    proj(2, 3) = -1;
    proj(3, 2) = 2 * near * far * rangeInv;

    return proj;
}