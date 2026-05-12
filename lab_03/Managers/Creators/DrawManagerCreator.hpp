#pragma once

#include "BaseManagerCreator.hpp"
#include "DrawManager.hpp"


class DrawManagerCreator : public BaseManagerCreator
{
    public:
        DrawManagerCreator() = default;
        virtual ~DrawManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            return std::make_shared<DrawManager>();
        }
};