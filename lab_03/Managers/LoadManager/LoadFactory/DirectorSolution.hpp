#pragma once

#include <memory>
#include "Director.hpp"

class DirectorSolution
{
    public:
        static std::shared_ptr<Director> create()
        {
            return std::make_shared<Director>();
        }
    };