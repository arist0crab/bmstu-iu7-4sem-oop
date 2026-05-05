#pragma once

#include "DrawManager.hpp"
#include "BaseManagerCreator.hpp"

class DrawManagerCreator : public BaseManagerCreator
{
    public:
        DrawManagerCreator() = default;
        virtual ~DrawManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            static auto instance = std::make_shared<DrawManager>();
            return instance;
        }
};
