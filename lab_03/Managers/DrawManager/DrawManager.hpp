#pragma once

#include <memory>
#include "BaseManager.hpp"
#include "BaseDrawer.hpp"
#include "DrawCarcassVisitor.hpp"
#include "DrawVisitor.hpp"
#include "ManagerSolution.hpp"
#include "CameraManager.hpp"
#include "SceneManager.hpp"

class DrawManager : public BaseManager
{
    public:
        DrawManager() = default;
        virtual ~DrawManager() override = default;

        void setDrawer(std::shared_ptr<BaseDrawer> drawer);
        void draw(std::shared_ptr<DrawVisitor> visitor);
        void drawScene();

    private:
        std::shared_ptr<BaseDrawer> m_drawer;
};