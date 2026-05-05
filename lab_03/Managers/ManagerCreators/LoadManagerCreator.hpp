#pragma once

#include "SceneManager.hpp"
#include "BaseManagerCreator.hpp"

class LoadManagerCreator : public BaseManagerCreator
{
    public:
        LoadManagerCreator() = default;
        virtual ~LoadManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            static auto instance = std::make_shared<SceneManager>();
            return instance;
        }
};
