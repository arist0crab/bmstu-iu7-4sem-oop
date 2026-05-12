#pragma once

#include <memory>
#include <vector>
#include "BaseObject.hpp"
#include "BaseVisitor.hpp"

class Scene
{
    public:
        static std::shared_ptr<Scene> getInstance();

        Scene(const Scene &other) = delete;
        Scene(Scene &&other) = delete;
        ~Scene() = default;

        size_t addObject(std::shared_ptr<BaseObject> object);
        std::shared_ptr<BaseObject> getObject(size_t id);
        void removeObject(size_t id);
        void clear();

        std::vector<std::shared_ptr<BaseObject>> getObjects() const;
        
        void accept(std::shared_ptr<BaseVisitor> visitor);

    private:
        Scene() = default;
        std::vector<std::shared_ptr<BaseObject>> m_objects;
};