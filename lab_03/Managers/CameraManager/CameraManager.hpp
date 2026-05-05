#pragma once 

#include <memory>
#include "BaseManager.hpp"

class CameraManager : public BaseManager
{
    public:
        CameraManager() = default;
        virtual ~CameraManager() override = default;

    private:
        std::shared_ptr<BaseCamera> m_activeCam;
        size_t m_activeCamId;
};

