#pragma once

#include <array>
#include <cmath>

#define TRANSFORM_MATRIX_SIZE 4

class Vertex;


class Transform
{
    public:
        ~Transform() noexcept = default;

        static Transform translation(double dx, double dy, double dz);
        static Transform translation(const Vertex &point);
        static Transform rotate(double angleX, double angleY, double angleZ);
        static Transform rotateX(double angleX);
        static Transform rotateY(double angleY);
        static Transform rotateZ(double angleZ);
        static Transform scale(double sx, double sy, double sz);
        static Transform scale(double uniform);
        static Transform identity();
        static Transform zero();

        void setTranslation(double dx, double dy, double dz) noexcept;
        void setRotation(double angleX, double angleY, double angleZ) noexcept;
        void setScale(double sx, double sy, double sz) noexcept;

        double operator()(size_t row, size_t col) const;
        double& operator()(size_t row, size_t col);
        
        Transform operator*(const Transform &other) const;
        Transform operator*=(const Transform &other);

    private:
        Transform() = default;

        static constexpr size_t SIZE = 4;
        std::array<std::array<double, SIZE>, SIZE> m_data;
};
