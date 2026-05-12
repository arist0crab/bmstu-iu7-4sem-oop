#include "CameraManager.hpp"

void CameraManager::setActiveCamera(size_t id)
{
    if (id < m_cameras.size())
        m_activeCamId = id;

    // TODO добавить соответствующее исключение
}

std::shared_ptr<BaseCamera> CameraManager::getActiveCamera() const noexcept
{
    if (m_cameras.empty())
        return nullptr;

    // TODO добавить соответствующее исключение

    return m_cameras[m_activeCamId];
}

size_t CameraManager::addCamera(std::shared_ptr<BaseCamera> camera)
{
    m_cameras.push_back(camera);
    
    return m_cameras.size() - 1;
}

void CameraManager::removeCamera(size_t id)
{
    if (id < m_cameras.size())
        m_cameras.erase(m_cameras.begin() + id);
}