#pragma once

#include <memory>
#include "BaseManager.hpp"

class BaseManagerCreator
{
    public:
        BaseManagerCreator() = default;
        virtual ~BaseManagerCreator() = default;
        
        virtual std::shared_ptr<BaseManager> create() = 0;
};

