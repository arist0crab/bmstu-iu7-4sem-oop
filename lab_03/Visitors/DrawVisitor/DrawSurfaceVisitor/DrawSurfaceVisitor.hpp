#pragma once

#include "DrawVisitor.hpp"
#include "BaseModel.hpp"
#include "BaseCameraImplementation.hpp"


class DrawSurfaceVisitor : public DrawVisitor
{
    public:
        DrawSurfaceVisitor() = default;
        virtual ~DrawSurfaceVisitor() override = default;

        void visit(BaseCameraImplementation &camera) const override;
        void visit(BaseStructure &structure) const override;
};