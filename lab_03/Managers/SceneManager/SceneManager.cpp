#include "SceneManager.hpp"


SceneManager::SceneManager()
{
    m_scene = Scene::getInstance();
}

std::shared_ptr<BaseObject> SceneManager::getObject(size_t id)
{
    return m_scene->getObject(id);
}

void SceneManager::addObject(std::shared_ptr<BaseObject> object)
{
    m_scene->addObject(object);
}

void SceneManager::removeObject(size_t id)
{
    m_scene->removeObject(id);
}

Vertex SceneManager::getCenter(size_t id) const
{
    auto obj = m_scene->getObject(id);
    return obj ? obj->getCenter() : Vertex(0, 0, 0);
}

void SceneManager::compose(std::vector<size_t> ids)
{
    auto composite = std::make_shared<Composite>();
    
    std::sort(ids.begin(), ids.end(), std::greater<size_t>());
    
    for (auto id : ids)
    {
        auto obj = m_scene->getObject(id);
        if (obj)
            composite->add(obj);
    }
    
    for (auto id : ids)
        m_scene->removeObject(id);
    
    m_scene->addObject(composite);
}

void SceneManager::accept(std::shared_ptr<BaseVisitor> visitor)
{
    m_scene->accept(visitor);
}

void SceneManager::clear()
{
	m_scene->clear();
}