#include "SceneManager.hpp"
#include "SceneException.hpp"
#include "ManagerSolution.hpp"
#include "CameraManager.hpp"


SceneManager::SceneManager()
{
    m_scene = Scene::getInstance();
}

std::shared_ptr<BaseObject> SceneManager::getObject(size_t id) const
{
    auto obj = m_scene->getObject(id);
    if (!obj)
        throw SceneObjectNotFoundException();
    return obj;
}

std::vector<std::shared_ptr<BaseObject>> SceneManager::getObjects() const
{
    return m_scene->getObjects();
}

void SceneManager::addObject(std::shared_ptr<BaseObject> object)
{
    if (!object)
        throw SceneInvalidOperationException("Cannot add null object");
    m_scene->addObject(object);
}

void SceneManager::removeObject(size_t id)
{
    auto obj = m_scene->getObject(id);
    if (!obj)
        throw SceneObjectNotFoundException();
    m_scene->removeObject(id);
}

Vertex SceneManager::getCenter(size_t id) const
{
    auto obj = m_scene->getObject(id);
    
    if (!obj)
        throw SceneObjectNotFoundException();

    return obj->getCenter();
}

void SceneManager::compose(std::vector<size_t> ids)
{
    if (ids.empty())
        throw SceneInvalidOperationException("Cannot compose empty list of objects");

    auto composite = std::make_shared<Composite>();
    
    std::sort(ids.begin(), ids.end(), std::greater<size_t>());
    
    for (auto id : ids)
    {
        auto obj = m_scene->getObject(id);
        if (!obj)
            throw SceneObjectNotFoundException();
        composite->add(obj);
    }
    
    for (auto id : ids)
        m_scene->removeObject(id);
    
    m_scene->addObject(composite);
}

void SceneManager::setCenter(size_t id, const Vertex &center)
{
    auto obj = m_scene->getObject(id);

    if (!obj)
        throw SceneObjectNotFoundException();

    obj->setCenter(center);
}

void SceneManager::toSurface(size_t id)
{
    // TODO
}

void SceneManager::accept(std::shared_ptr<BaseVisitor> visitor)
{
    if (!visitor)
        throw SceneInvalidOperationException("Cannot accept null visitor");

    for (auto &obj : m_scene->getObjects())
        obj->accept(visitor);
}

void SceneManager::initScene()
{
    auto cameraManager = ManagerSolution::getManager<CameraManager>();
    cameraManager->addDefaultCamera();
}

void SceneManager::clear()
{
	m_scene->clear();
}