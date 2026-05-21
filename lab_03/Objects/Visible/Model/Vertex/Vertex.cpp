#include "Vertex.hpp"

Vertex::Vertex(double x, double y, double z) : m_x(x), m_y(y), m_z(z), m_w(1.0) { }

double Vertex::X() const noexcept
{
    return m_x;
}

double Vertex::Y() const noexcept
{
    return m_y;
}

double Vertex::Z() const noexcept
{
    return m_z;
}

double Vertex::W() const noexcept
{
    return m_w;
}

void Vertex::setX(const double x) noexcept
{
    m_x = x;
}

void Vertex::setY(const double y) noexcept
{
    m_y = y;
}

void Vertex::setZ(const double z) noexcept
{
    m_z = z;
}

void Vertex::setW(const double w) noexcept
{
    m_w = w;
}

double Vertex::calculateDistance(const Vertex &other) const
{
    const double dx = other.m_x - m_x;
    const double dy = other.m_y - m_y;
    const double dz = other.m_z - m_z;

    return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2) + std::pow(dz, 2));
}

void Vertex::transform(const Transform &transform)
{
    double x = m_x;
    double y = m_y;
    double z = m_z;
    
    m_x = x * transform(0,0) + y * transform(1,0) + z * transform(2,0) + transform(3,0);
    m_y = x * transform(0,1) + y * transform(1,1) + z * transform(2,1) + transform(3,1);
    m_z = x * transform(0,2) + y * transform(1,2) + z * transform(2,2) + transform(3,2);
}

Vertex Vertex::normalize() const
{
    double len = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);

    if (len < EPS)
        return Vertex(0, 0, 0);

    return Vertex(m_x / len, m_y / len, m_z / len);
}

Vertex Vertex::cross(const Vertex &other) const
{
    return Vertex(
        m_y * other.m_z - m_z * other.m_y,
        m_z * other.m_x - m_x * other.m_z,
        m_x * other.m_y - m_y * other.m_x
    );
}

double Vertex::dot(const Vertex &other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

bool Vertex::equal(const Vertex &other) const noexcept
{
    const bool x_equal = other.m_x == m_x;
    const bool y_equal = other.m_y == m_y;
    const bool z_equal = other.m_z == m_z;
    const bool w_equal = other.m_w == m_w;

    return x_equal && y_equal && z_equal && w_equal;
}

Vertex& Vertex::add(const Vertex &other) noexcept
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;

    return *this;
}

Vertex& Vertex::subtract(const Vertex &other) noexcept
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;

    return *this;
}

Vertex Vertex::make_sum(const Vertex &other) const
{
    Vertex res(*this);
    res += other;

    return res;
}

Vertex Vertex::make_diff(const Vertex &other) const
{
    Vertex res(*this);
    res -= other;

    return res;
}  

Vertex& Vertex::operator+=(const Vertex &other) noexcept
{
    add(other);
    return *this;
}   

Vertex& Vertex::operator-=(const Vertex &other) noexcept
{
    subtract(other);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vertex &vertex)
{
    os << "(" << vertex.X() << ", " << vertex.Y() << ", " << vertex.Z() << ", " <<  vertex.W() << ")";
    return os;
}

Vertex operator+(const Vertex &lhs, const Vertex &rhs)
{
    return lhs.make_sum(rhs); 
}

Vertex operator-(const Vertex &lhs, const Vertex &rhs)
{
    return lhs.make_diff(rhs); 
}
