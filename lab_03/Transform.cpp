#include "Transform.hpp"
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
        {1, 0, 0, 0},
        {0, c, s, 0},
        {0, -s, c, 0},
        {0, 0, 0, 1}
    }};
    return t;
}

Transform Transform::rotateY(double angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);

    Transform t;
    t.m_data = {{
        {c, 0, -s, 0},
        {0, 1, 0, 0},
        {s, 0, c, 0},
        {0, 0, 0, 1}
    }};
    return t;
}

Transform Transform::rotateZ(double angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);

    Transform t;
    t.m_data = {{
        {c, s, 0, 0},
        {-s, c, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
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

Transform Transform::zero()
{
    Transform t;
    
    for (auto &row : t.m_data)
        row.fill(0);

    return t;
}

Transform Transform::operator*(const Transform &other) const
{
    Transform t = Transform::zero();

    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            for (size_t k = 0; k < SIZE; k++)
                t.m_data[i][j] += m_data[k][i] * other.m_data[j][k];

    return t;

}

Transform Transform::operator*=(const Transform &other)
{
    *this = *this * other;
    return *this;
}