#include "CameraManager.hpp"
#include "CameraException.hpp"


void CameraManager::setActiveCamera(size_t id)
{
    if (id >= m_cameras.size())
        throw CameraNotFoundException("Camera id out of range");

    m_activeCamId = id;
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

    if (m_activeCamId >= m_cameras.size())
        m_activeCamId = m_cameras.empty() ? 0 : m_cameras.size() - 1;
}

size_t CameraManager::addDefaultCamera()
{
    auto camera = std::make_shared<DefaultCamera>(Vertex(0, 0, 100), Vertex(0, 0, 0));
    m_cameras.push_back(camera);
    m_activeCamId = m_cameras.size() - 1;

    return m_activeCamId;
}