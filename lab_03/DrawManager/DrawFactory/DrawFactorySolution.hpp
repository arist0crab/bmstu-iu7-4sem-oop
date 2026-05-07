#pragma once

#include <memory>
#include "BaseDrawerCreator.hpp"

class DrawFactorySolution 
{
    public:
        template <typename TFactory, typename TScene>
        static std::unique_ptr<BaseDrawerCreator> createDrawer(std::shared_ptr<TScene> scene);
};