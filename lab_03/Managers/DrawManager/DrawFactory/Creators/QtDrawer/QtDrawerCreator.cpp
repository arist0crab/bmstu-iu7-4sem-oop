#include "QtDrawerCreator.hpp"

QtDrawerCreator::QtDrawerCreator(std::shared_ptr<QGraphicsScene> scene) : m_scene(scene) { }

std::unique_ptr<BaseDrawer> QtDrawerCreator::createDrawer()
{
    return std::make_unique<QtDrawer>(m_scene);
}
