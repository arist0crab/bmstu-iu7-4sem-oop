#include "DrawManager.hpp"


void DrawManager::setDrawer(std::shared_ptr<BaseDrawer> drawer)
{
    m_drawer = drawer;
}

void DrawManager::draw(std::shared_ptr<DrawVisitor> visitor)
{
    m_drawer->clear();

    auto cameraManager = ManagerSolution::getManager<CameraManager>();
    auto activeCamera = cameraManager->getActiveCamera();
    
    if (activeCamera)
        visitor->setCamera(activeCamera->getImplementation());
    visitor->setDrawer(m_drawer);

    auto sceneManager = ManagerSolution::getManager<SceneManager>();
    sceneManager->accept(visitor);
}

void DrawManager::drawScene()
{
    auto visitor = std::make_shared<DrawCarcassVisitor>();    
    this->draw(visitor); 
}