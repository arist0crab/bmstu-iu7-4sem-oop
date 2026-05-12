#include "Scene.hpp"

std::shared_ptr<Scene> Scene::getInstance()
{
    static auto instance = std::shared_ptr<Scene>(new Scene());
    return instance;
}

size_t Scene::addObject(std::shared_ptr<BaseObject> object)
{
    m_objects.push_back(object);
    return m_objects.size() - 1;
}

std::shared_ptr<BaseObject> Scene::getObject(size_t id)
{
    return (id < m_objects.size()) ? m_objects[id] : nullptr;
}

void Scene::removeObject(size_t id)
{
    if (id < m_objects.size())
        m_objects.erase(m_objects.begin() + id);
}

void Scene::clear()
{
    m_objects.clear();
}

std::vector<std::shared_ptr<BaseObject>> Scene::getObjects() const
{
    return m_objects;
}

void Scene::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto &obj : m_objects)
        obj->accept(visitor);
}