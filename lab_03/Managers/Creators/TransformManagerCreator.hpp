#pragma once

#include "BaseManagerCreator.hpp"
#include "TransformManager.hpp"


class TransformManagerCreator : public BaseManagerCreator
{
    public:
        TransformManagerCreator() = default;
        virtual ~TransformManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            return std::make_shared<TransformManager>();
        }
};