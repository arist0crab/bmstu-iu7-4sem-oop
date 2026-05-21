#include "SceneCommand.hpp"
#include "CameraManager.hpp"
#include "DrawManager.hpp"
#include "SceneManager.hpp"

InitSceneCommand::InitSceneCommand() : m_action(&SceneManager::initScene) {}

void InitSceneCommand::execute()
{
    ((*m_sceneManager).*m_action)();
}

DrawSceneCommand::DrawSceneCommand() : m_action(&DrawManager::drawScene) {}

void DrawSceneCommand::execute()
{
    ((*m_drawManager).*m_action)(); 
}

ClearSceneCommand::ClearSceneCommand() : m_action(&SceneManager::clear) {}

void ClearSceneCommand::execute()
{
    ((*m_sceneManager).*m_action)();
}