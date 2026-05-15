#pragma once

#include <memory>

class DrawManager;
class LoadManager;
class SceneManager;
class TransformManager;
class CameraManager;


class BaseCommand
{
    public:
        BaseCommand() = default;
        virtual ~BaseCommand() = default;

        virtual void execute() = 0;

        void setManagers(std::shared_ptr<DrawManager> drawManager,
                        std::shared_ptr<LoadManager> loadManager,
                        std::shared_ptr<SceneManager> sceneManager,
                        std::shared_ptr<TransformManager> transformManager,
                        std::shared_ptr<CameraManager> cameraManager)
        {
            m_drawManager = drawManager;
            m_loadManager = loadManager;
            m_sceneManager = sceneManager;
            m_transformManager = transformManager;
            m_cameraManager = cameraManager;
        }

    protected:
        std::shared_ptr<DrawManager> m_drawManager;
        std::shared_ptr<LoadManager> m_loadManager;
        std::shared_ptr<SceneManager> m_sceneManager;
        std::shared_ptr<TransformManager> m_transformManager;
        std::shared_ptr<CameraManager> m_cameraManager;
};