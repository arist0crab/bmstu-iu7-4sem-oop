#pragma once

#include <memory>
#include "BaseDrawer.hpp"

class BaseDrawerCreator
{
    public:
        BaseDrawerCreator() = default;
        virtual ~BaseDrawerCreator() = default;

        virtual std::unique_ptr<BaseDrawer> createDrawer() = 0;
};