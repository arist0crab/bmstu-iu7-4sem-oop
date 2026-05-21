#pragma once

#include <memory>
#include <vector>
#include "BaseCamera.hpp"
#include "DefaultCamera.hpp"
#include "BaseManager.hpp"

class CameraManager : public BaseManager
{
    public:
        CameraManager() = default;
        virtual ~CameraManager() override = default;

        void setActiveCamera(size_t id);
        size_t getActiveCameraId() const noexcept;
        std::shared_ptr<BaseCamera> getCamera(size_t id) const;
        std::shared_ptr<BaseCamera> getActiveCamera() const noexcept;

        size_t addDefaultCamera();
        void removeCamera(size_t id);

    private:
        std::vector<std::shared_ptr<BaseCamera>> m_cameras;
        size_t m_activeCamId = 0;
};