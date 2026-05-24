#pragma once

#include <memory>
#include "BaseDrawer.hpp"

class BaseDrawerFactory
{
    public:
        BaseDrawerFactory() = default;
        virtual ~BaseDrawerFactory() = default;

        virtual std::unique_ptr<BaseDrawer> createDrawer() const = 0;
};