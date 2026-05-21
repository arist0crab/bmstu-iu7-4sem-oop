#include "CameraManager.hpp"
#include "CameraException.hpp"


void CameraManager::setActiveCamera(size_t id)
{
    if (id >= m_cameras.size())
        throw CameraNotFoundException("Camera id out of range");

    m_activeCamId = id;
}

size_t CameraManager::getActiveCameraId() const noexcept
{
    return m_activeCamId;
}

std::shared_ptr<BaseCamera> CameraManager::getCamera(size_t id) const
{
    if (id >= m_cameras.size())
        throw CameraNotFoundException("Camera id out of range");

    return m_cameras[id];
}

std::shared_ptr<BaseCamera> CameraManager::getActiveCamera() const noexcept
{
    return m_cameras.empty() ? nullptr : m_cameras[m_activeCamId];
}

void CameraManager::removeCamera(size_t id)
{
    if (id >= m_cameras.size()) 
        throw CameraNotFoundException("Camera id out of range");

    m_cameras.erase(m_cameras.begin() + id);

    if (id < m_activeCamId)
        m_activeCamId--;
    else if (id == m_activeCamId)
        m_activeCamId = m_cameras.empty() ? 0 : 0; 
}

size_t CameraManager::addDefaultCamera()
{
    auto camera = std::make_shared<DefaultCamera>(Vertex(0, 0, 100), Vertex(0, 0, 0));
    m_cameras.push_back(camera);
    m_activeCamId = m_cameras.size() - 1;

    return m_activeCamId;
}