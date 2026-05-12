#pragma once

#include <iostream>
#include "Transform.hpp"

#define EPS 1e-9

class Vertex
{
    public:
        Vertex() = default;
        Vertex(double x, double y, double z);

        Vertex(const Vertex &other) = default;
        Vertex(Vertex &&other) = default;

        ~Vertex() = default;

        Vertex &operator=(const Vertex &other) = default;
        Vertex &operator=(Vertex &&other) = default;

        double X() const noexcept;
        double Y() const noexcept;
        double Z() const noexcept;
        double W() const noexcept;

        void setX(const double x) noexcept;
        void setY(const double y) noexcept;
        void setZ(const double z) noexcept;
        void setW(const double w) noexcept;

        double calculateDistance(const Vertex &other) const;
        void transform(const Transform &transform);

        Vertex normalize() const;
        Vertex cross(const Vertex &other) const;
        double dot(const Vertex &other) const;

        bool equal(const Vertex &other) const noexcept;
        auto operator<=>(const Vertex &other) const = default;

        Vertex &add(const Vertex &other) noexcept;
        Vertex &subtract(const Vertex &other) noexcept;
        Vertex make_sum(const Vertex &other) const;
        Vertex make_diff(const Vertex &other) const;    

        Vertex &operator+=(const Vertex &other) noexcept;
        Vertex &operator-=(const Vertex &other) noexcept;


    private:
        double m_x, m_y, m_z, m_w;
};

std::ostream &operator<<(std::ostream &os, const Vertex &vertex);

Vertex operator+(const Vertex &lhs, const Vertex &rhs);

Vertex operator-(const Vertex &lhs, const Vertex &rhs);