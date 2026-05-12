#pragma once

#include <memory>
#include "BaseVisitor.hpp"
#include "BaseCamera.hpp"
#include "BaseDrawer.hpp"


class DrawVisitor : public BaseVisitor
{
    public:
        DrawVisitor() = default;
        virtual ~DrawVisitor() override = default;

        void setCamera(std::shared_ptr<BaseCamera> camera) { m_camera = camera; }
        void setDrawer(std::shared_ptr<BaseDrawer> drawer) { m_drawer = drawer; }

    protected:
        std::shared_ptr<BaseCamera> m_camera;
        std::shared_ptr<BaseDrawer> m_drawer;
};