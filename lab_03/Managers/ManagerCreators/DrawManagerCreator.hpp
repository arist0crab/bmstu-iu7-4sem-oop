#pragma once

#include "SceneManager.hpp"
#include "BaseManagerCreator.hpp"

class SceneManagerCreator : public BaseManagerCreator
{
    public:
        SceneManagerCreator() = default;
        virtual ~SceneManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            static auto instance = std::make_shared<SceneManager>();
            return instance;
        }
};
