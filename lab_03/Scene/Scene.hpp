#pragma once

#include <memory>
#include <vector>
#include "BaseObject.hpp"

class Scene
{
    public:
        static std::shared_ptr<Scene> getInstance();

        Scene(const Scene &other) = delete;
        Scene(Scene &&other) = delete;
        Scene &operator=(const Scene &other) = delete;
        Scene &operator=(Scene &&other) = delete;
        ~Scene() = default;

        std::shared_ptr<BaseObject> getObject(size_t id);
        const std::vector<std::shared_ptr<BaseObject>>& getObjects() const;

        size_t addObject(std::shared_ptr<BaseObject> object);
        void removeObject(size_t id);
        void clear();

    private:
        Scene() = default;
        std::vector<std::shared_ptr<BaseObject>> m_objects;
};