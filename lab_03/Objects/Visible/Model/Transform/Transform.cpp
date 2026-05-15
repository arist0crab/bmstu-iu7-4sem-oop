#include "Transform.hpp"
#include "Vertex.hpp"
#include <cmath>

Transform Transform::translation(double dx, double dy, double dz)
{
    Transform t;
    t.m_data = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {dx, dy, dz, 1}
    }};
    return t;
}

Transform Transform::translation(const Vertex &point)
{
    const double dx = point.X();
    const double dy = point.Y();
    const double dz = point.Z();

    return Transform::translation(dx, dy, dz);
}

Transform Transform::rotate(double angleX, double angleY, double angleZ)
{
    return rotateZ(angleZ) * rotateY(angleY) * rotateX(angleX);
}

Transform Transform::rotateX(double angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    Transform t;
    t.m_data = {{
        {1, 0,  0, 0},
        {0, c, -s, 0},
        {0, s,  c, 0},
        {0, 0,  0, 1}
    }};
    return t;
}

Transform Transform::rotateY(double angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    Transform t;
    t.m_data = {{
        { c, 0, s, 0},
        { 0, 1, 0, 0},
        {-s, 0, c, 0},
        { 0, 0, 0, 1}
    }};
    return t;
}

Transform Transform::rotateZ(double angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    Transform t;
    t.m_data = {{
        { c, s, 0, 0},
        {-s, c, 0, 0},
        { 0, 0, 1, 0},
        { 0, 0, 0, 1}
    }};
    return t;
}

Transform Transform::scale(double sx, double sy, double sz)
{
    Transform t;
    t.m_data = {{
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    }};
    return t;
}

Transform Transform::scale(double uniform)
{
    return scale(uniform, uniform, uniform);
}

Transform Transform::identity()
{
    Transform t;
    t.m_data = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    return t;
}

Transform Transform::zero()
{
    Transform t;
    
    for (auto &row : t.m_data)
        row.fill(0);

    return t;
}

void Transform::setTranslation(double dx, double dy, double dz) noexcept
{
    m_data[3][0] = dx;
    m_data[3][1] = dy;
    m_data[3][2] = dz;
}

void Transform::setRotation(double angleX, double angleY, double angleZ) noexcept
{
    Transform rot = rotate(angleX, angleY, angleZ);
    
    double dx = m_data[3][0];
    double dy = m_data[3][1];
    double dz = m_data[3][2];
    
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m_data[i][j] = rot(i, j);
    
    m_data[3][0] = dx;
    m_data[3][1] = dy;
    m_data[3][2] = dz;
}

void Transform::setScale(double sx, double sy, double sz) noexcept
{
    Transform scl = scale(sx, sy, sz);
    
    double dx = m_data[3][0];
    double dy = m_data[3][1];
    double dz = m_data[3][2];
    
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m_data[i][j] = scl(i, j);
    
    m_data[3][0] = dx;
    m_data[3][1] = dy;
    m_data[3][2] = dz;
}

double Transform::operator()(size_t row, size_t col) const
{
    return m_data[row][col];
}

double& Transform::operator()(size_t row, size_t col)
{
    return m_data[row][col];
}

Transform Transform::operator*(const Transform &other) const
{
    Transform t = Transform::zero();

    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            for (size_t k = 0; k < SIZE; k++)
                t.m_data[i][j] += m_data[i][k] * other.m_data[k][j];

    return t;
}

Transform Transform::operator*=(const Transform &other)
{
    *this = *this * other;
    return *this;
}