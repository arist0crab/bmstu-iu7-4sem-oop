#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "Scene.hpp"
#include "BaseManager.hpp"
#include "Composite.hpp"


class SceneManager : public BaseManager
{
    public:
        SceneManager();
        virtual ~SceneManager() override = default;

        std::shared_ptr<BaseObject> getObject(size_t id) const;
        std::vector<std::shared_ptr<BaseObject>> getObjects() const;
        Vertex getCenter(size_t id) const;

        void addObject(std::shared_ptr<BaseObject> object);
        void removeObject(size_t id);
        void setCenter(size_t id, const Vertex &center);
        void toSurface(size_t id);

        void compose(std::vector<size_t> ids);
        void accept(std::shared_ptr<BaseVisitor> visitor);

        void initScene();
        void clear();

    private:
        std::shared_ptr<Scene> m_scene;
};