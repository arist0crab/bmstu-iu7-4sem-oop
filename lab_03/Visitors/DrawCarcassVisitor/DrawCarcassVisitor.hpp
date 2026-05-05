#pragma once

#include <memory>
#include "BasePainter.hpp"
#include "BaseVisitor.hpp"

class DrawCarcassVisitor : BaseVisitor
{
    public:
        DrawCarcassVisitor(std::shared_ptr<BasePainter> painter, std::shared_ptr<BaseCamera> camera);
        virtual ~DrawCarcassVisitor() override = default;

        void visit(BaseModel &model) const override;
        void visit(BaseCamera &camera) const override;

    private:
        std::shared_ptr<BasePainter> m_painter;
        std::shared_ptr<BaseCamera> m_camera;
};