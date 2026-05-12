#pragma once

#include "BaseManagerCreator.hpp"
#include "CameraManager.hpp"


class CameraManagerCreator : public BaseManagerCreator
{
    public:
        CameraManagerCreator() = default;
        virtual ~CameraManagerCreator() override = default;

        std::shared_ptr<BaseManager> create() override
        {
            return std::make_shared<CameraManager>();
        }
};