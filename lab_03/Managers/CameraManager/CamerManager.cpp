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

size_t CameraManager::addDefaultCamera()
{
    auto camera = std::make_shared<DefaultCamera>(Vertex(0, 0, 100), Vertex(0, 0, 0));
    m_cameras.push_back(camera);
    m_activeCamId = m_cameras.size() - 1;

    return m_activeCamId;
}

void CameraManager::removeCamera(size_t id)
{
    if (id < m_cameras.size())
        m_cameras.erase(m_cameras.begin() + id);
}