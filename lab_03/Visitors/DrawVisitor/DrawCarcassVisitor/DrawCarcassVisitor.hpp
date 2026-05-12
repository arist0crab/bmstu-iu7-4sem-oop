#pragma once

#include "DrawVisitor.hpp"
#include "BaseModel.hpp"

class DrawCarcassVisitor : public DrawVisitor
{
    public:
        DrawCarcassVisitor() = default;
        virtual ~DrawCarcassVisitor() override = default;

        void visit(BaseCamera &camera) const override;
        void visit(BaseModel &model) const override;
};