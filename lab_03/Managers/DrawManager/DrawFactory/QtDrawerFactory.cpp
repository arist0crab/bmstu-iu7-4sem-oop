#include "QtDrawerFactory.hpp"
#include "QtDrawer.hpp"

QtDrawerFactory::QtDrawerFactory(std::shared_ptr<QGraphicsScene> scene) : m_scene(scene) { }

std::unique_ptr<BaseDrawer> QtDrawerFactory::createDrawer() const
{
    return std::make_unique<QtDrawer>(m_scene);
}