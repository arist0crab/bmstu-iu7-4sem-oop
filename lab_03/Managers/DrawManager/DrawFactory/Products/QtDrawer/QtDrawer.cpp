#include "QtDrawer.hpp"

QtDrawer::QtDrawer(std::shared_ptr<QGraphicsScene> scene) : m_scene(scene), m_color(Qt::white)
{
    m_sceneWidth = m_scene->width();
    m_sceneHeight = m_scene->height();
}

size_t QtDrawer::getWidth() const noexcept
{
    return m_sceneWidth;
}

size_t QtDrawer::getHeight() const noexcept
{
    return m_sceneHeight;
}

void QtDrawer::clear()
{
    m_scene->clear();
}

void QtDrawer::setColor(const QColor &newColor) noexcept
{
    m_color = newColor;
}

void QtDrawer::drawLine(const double x1, const double y1, const double x2, const double y2)
{
    m_scene->addLine(x1, y1, x2, y2, { m_color });
}

void QtDrawer::drawLine(const Vertex &v1, const Vertex &v2)
{
    const double x1 = v1.X();
    const double y1 = v1.Y();
    const double x2 = v2.X();
    const double y2 = v2.Y();
    m_scene->addLine(x1, y1, x2, y2, { m_color });
}
