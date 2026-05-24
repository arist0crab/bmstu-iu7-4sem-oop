#pragma once

#include <memory>
#include "BaseVisitor.hpp"
#include "Transform.hpp"
#include "BaseCameraImplementation.hpp"

class TransformVisitor : public BaseVisitor
{
    public:
        TransformVisitor() = delete;
        TransformVisitor(const Transform &transform);
        virtual ~TransformVisitor() override = default;

        void visit(BaseCameraImplementation &camera) const override;
        void visit(BaseStructure &structure) const override;

    protected:
        Transform m_transform;
};