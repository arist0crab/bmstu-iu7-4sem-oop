#pragma once

#include <memory>
#include <vector>
#include "BaseObject.hpp"
#include "Transform.hpp"
#include "BaseVisitor.hpp"

class Composite : public BaseObject
{
    public:
        Composite() = default;
        virtual ~Composite() override = default;

        std::shared_ptr<BaseObject> getObject(const size_t id) const override;
        void add(std::shared_ptr<BaseObject> object) override;
        void remove(const size_t id) noexcept override;
        void accept(std::shared_ptr<BaseVisitor> visitor) override;

        Vertex getCenter() const noexcept override;
        void setCenter(const Vertex &point) override;
        void transform(const Transform &transform) override;
        
        bool isComposite() const noexcept override { return true; }
        bool isVisible() const noexcept override { return true; }

    private:
        std::vector<std::shared_ptr<BaseObject>> m_objects;
};