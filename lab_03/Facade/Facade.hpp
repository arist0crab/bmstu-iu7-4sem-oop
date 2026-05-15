#pragma once

#include <memory>
#include "BaseCommand.hpp"

class DrawManager;
class LoadManager;
class SceneManager;
class TransformManager;
class CameraManager;


class Facade
{
    public:
        Facade();
        ~Facade() = default;

        void execute(std::shared_ptr<BaseCommand> command);

    private:
        std::shared_ptr<DrawManager> m_drawManager;
        std::shared_ptr<LoadManager> m_loadManager;
        std::shared_ptr<SceneManager> m_sceneManager;
        std::shared_ptr<TransformManager> m_transformManager;
        std::shared_ptr<CameraManager> m_cameraManager;
};