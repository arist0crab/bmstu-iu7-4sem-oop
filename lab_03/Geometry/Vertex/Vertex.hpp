#pragma once

#include "Transform.hpp"

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

        void setX() noexcept;
        void setY() noexcept;
        void setZ() noexcept;
        void setW() noexcept;

        double calculateDistance(const Vertex &other) const;
        void transform(const Transform &transform);

        bool equal(const Vertex &other) const noexcept;
        auto operator<==>(const Vertex w)



    private:
        double m_x, m_y, m_z, m_w;
};