#pragma once

#include "BaseManagerCreator.hpp"
#include "SceneManager.hpp"


class SceneManagerCreator : public BaseManagerCreator
{
    public:
        SceneManagerCreator() = default;
        virtual ~SceneManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            return std::make_shared<SceneManager>();
        }
};