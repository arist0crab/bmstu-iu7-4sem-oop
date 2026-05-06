#pragma once

#include "Vertex.hpp"


class BaseDrawer
{
    public:
        BaseDrawer() = default;
        virtual ~BaseDrawer() = default;

        virtual size_t getWidth() const noexcept = 0;
        virtual size_t getHeight() const noexcept = 0;

        virtual void clear() = 0;
        virtual void drawLine(const Vertex &v1, const Vertex &v2) = 0;
        virtual void drawLine(const double x1, const double y1, const double x2, const double y2) = 0;

    protected:
        size_t m_sceneWidth;
        size_t m_sceneHeight;
};