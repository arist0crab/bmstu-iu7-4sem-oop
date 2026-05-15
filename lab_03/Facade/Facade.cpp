#include "Facade.hpp"
#include "ManagerSolution.hpp"
#include "DrawManager.hpp"
#include "LoadManager.hpp"
#include "SceneManager.hpp"
#include "TransformManager.hpp"
#include "CameraManager.hpp"


Facade::Facade()
{
    m_drawManager = ManagerSolution::getManager<DrawManager>();
    m_loadManager = ManagerSolution::getManager<LoadManager>();
    m_sceneManager = ManagerSolution::getManager<SceneManager>();
    m_transformManager = ManagerSolution::getManager<TransformManager>();
    m_cameraManager = ManagerSolution::getManager<CameraManager>();
}

void Facade::execute(std::shared_ptr<BaseCommand> command)
{
    command->setManagers(m_drawManager, m_loadManager, m_sceneManager, m_transformManager, m_cameraManager);
    command->execute();
}