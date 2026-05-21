#pragma once

#include <memory>
#include "Vertex.hpp"

class BaseVisitor;

class BaseObject
{
    public:
        BaseObject() = default;
        virtual ~BaseObject() = default;

        virtual bool isVisible() const noexcept = 0;
        virtual bool isComposite() const noexcept = 0;

        Vertex getCenter() const noexcept;
        void setCenter(const Vertex &center) noexcept;

        virtual void add(std::shared_ptr<BaseObject> object);
        virtual void remove(const size_t id) noexcept;

        virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;

    protected:
        Vertex m_center;
};