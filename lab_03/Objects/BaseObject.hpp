#pragma once

#include <memory>
#include "Vertex.hpp"
#include "Transform.hpp"
#include "BaseVisitor.hpp"

class BaseObject
{
    public:
        BaseObject() = default;
        virtual ~BaseObject() = default;

        virtual bool isVisible() const noexcept = 0;
        virtual bool isComposite() const noexcept = 0;

        virtual std::shared_ptr<BaseObject> getObject(const size_t id) const;
        
        virtual void add(std::shared_ptr<BaseObject> object) = 0;
        virtual void remove(const size_t id) noexcept = 0;

        virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;

        virtual void setCenter(const Vertex &point) = 0;
        virtual void setLocalCenter(const Vertex &point);
        virtual void setLocalTransform(const Transform &transform);

        virtual Vertex getCenter() const noexcept = 0;
        virtual Vertex getLocalCenter() const noexcept;
        virtual Transform getLocalTransform() const noexcept;

    protected:
        Vertex m_localCenter;
        Transform m_localTransform;
};