#pragma once

#include <memory>
#include "BaseVisitor.hpp"

class BaseObject
{
    public:
        BaseObject() = default;
        virtual ~BaseObject() = default;

        virtual bool isVisible() const noexcept = 0;
        virtual bool isComposite() const noexcept = 0;

        virtual std::shared_ptr<BaseObject> get(const size_t id) const;
        virtual void add(std::shared_ptr<BaseObject> object);
        virtual void remove(const size_t id) noexcept;

        virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;

        // TODO как работать с центром?
};