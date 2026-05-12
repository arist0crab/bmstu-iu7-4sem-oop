#pragma once

#include <memory>
#include "BaseBuilder.hpp"

class BuilderSolution
{
    public:
        template <typename TBuilder>
        static std::shared_ptr<BaseBuilder> create()
        {
            return std::make_shared<TBuilder>();
        }
};