#pragma once

#include "DrawVisitor.hpp"
#include "BaseModel.hpp"


class DrawSurfaceVisitor : public DrawVisitor
{
    public:
        DrawSurfaceVisitor() = default;
        virtual ~DrawSurfaceVisitor() override = default;

        void visit(BaseCamera &camera) const override;
        void visit(BaseStructure &structure) const override;
};