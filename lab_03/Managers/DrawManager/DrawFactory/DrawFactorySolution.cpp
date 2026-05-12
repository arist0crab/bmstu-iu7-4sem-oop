#include "DrawFactorySolution.hpp"


template <typename TFactory, typename TScene>
std::unique_ptr<BaseDrawer> DrawFactorySolution::createDrawer(std::shared_ptr<TScene> scene)
{
    std::shared_ptr<BaseDrawerCreator> creator = std::make_shared<TFactory>(scene);
    return creator->createDrawer();
}   