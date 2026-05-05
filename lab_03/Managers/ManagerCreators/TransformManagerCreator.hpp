#pragma once

#include "TransformManager.hpp"
#include "BaseManagerCreator.hpp"

class TransformManagerCreator : public BaseManagerCreator
{
    public:
        TransformManagerCreator() = default;
        virtual ~TransformManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            static auto instance = std::make_shared<TransformManager>();
            return instance;
        }
};
