#pragma once

#include "CameraManager.hpp"
#include "BaseManagerCreator.hpp"

class CameraManagerCreator : public BaseManagerCreator
{
    public:
        CameraManagerCreator() = default;
        virtual ~CameraManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            static auto instance = std::make_shared<CameraManager>();
            return instance;
        }
};
