#pragma once

#include <memory>
#include <QGraphicsScene>
#include "BaseDrawer.hpp"

#define SAND_COLOR QColor(226, 194, 155)


class QtDrawer : public BaseDrawer
{
    public:
        QtDrawer() = delete;
        QtDrawer(std::shared_ptr<QGraphicsScene> scene);
        virtual ~QtDrawer() override = default;

        size_t getWidth() const noexcept override;
        size_t getHeight() const noexcept override;

        void clear() override;
        void setColor(const QColor &newColor) noexcept;
        void drawLine(const Vertex &v1, const Vertex &v2) override;
        void drawLine(const double x1, const double y1, const double x2, const double y2) override;

    private:
        QColor m_color = SAND_COLOR;
        std::shared_ptr<QGraphicsScene> m_scene;
};