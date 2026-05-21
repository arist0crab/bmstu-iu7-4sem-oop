#include "SceneCommand.hpp"
#include "CameraManager.hpp"
#include "DrawManager.hpp"
#include "DrawCarcassVisitor.hpp"
#include "SceneManager.hpp"


InitSceneCommand::InitSceneCommand()
    : m_addAction(&CameraManager::addDefaultCamera)
    , m_setAction(&CameraManager::setActiveCamera) {}

void InitSceneCommand::execute()
{
    auto cameraManager = ManagerSolution::getManager<CameraManager>();
    auto sceneManager = ManagerSolution::getManager<SceneManager>();

    size_t localCamId = cameraManager->addDefaultCamera();
    std::shared_ptr<BaseCamera> camera = cameraManager->getCamera(localCamId);

    sceneManager->addObject(camera);
    cameraManager->setActiveCamera(localCamId);
}

DrawSceneCommand::DrawSceneCommand()
    : m_action(&DrawManager::draw) {}

void DrawSceneCommand::execute()
{
    auto visitor = std::make_shared<DrawCarcassVisitor>();
    ((*m_drawManager).*m_action)(visitor);
}

ClearSceneCommand::ClearSceneCommand()
    : m_action(&SceneManager::clear) {}

void ClearSceneCommand::execute()
{
    ((*m_sceneManager).*m_action)();
}