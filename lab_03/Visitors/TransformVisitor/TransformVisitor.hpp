#pragma once

#include <memory>
#include "BaseVisitor.hpp"
#include "Transform.hpp"

class TransformVisitor : public BaseVisitor
{
    public:
        TransformVisitor() = delete;
        TransformVisitor(const Transform &transform);
        virtual ~TransformVisitor() override = default;

        void visit(BaseCamera &camera) const override;
        void visit(BaseModel &model) const override;

    protected:
        Transform m_transform;
};