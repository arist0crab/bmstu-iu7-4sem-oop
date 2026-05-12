#pragma once

#include "BaseManagerCreator.hpp"
#include "LoadManager.hpp"


class LoadManagerCreator : public BaseManagerCreator
{
    public:
        LoadManagerCreator() = default;
        virtual ~LoadManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            return std::make_shared<LoadManager>();
        }
};