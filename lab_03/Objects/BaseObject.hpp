#pragma once

#include <memory>
#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Transform.hpp"
#include "BaseVisitor.hpp"

class BaseObject
{
    public:
        BaseObject() = default;
        virtual ~BaseObject() = default;

        virtual bool isVisible() const noexcept = 0;
        virtual bool isComposite() const noexcept = 0;

        virtual Vertex getCenter() const noexcept = 0;
        virtual void setCenter(const Vertex &point) = 0;
        virtual void transform(const Transform &transform) = 0;

        virtual std::shared_ptr<BaseObject> getObject(const size_t id) const;
        virtual void add(std::shared_ptr<BaseObject> object);
        virtual void remove(const size_t id) noexcept;

        virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;
};