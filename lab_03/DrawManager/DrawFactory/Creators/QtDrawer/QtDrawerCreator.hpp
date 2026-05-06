#pragma once

#include "BaseDrawerCreator.hpp"
#include "QtDrawer.hpp"
#include <memory>
#include <QGraphicsScene>

class QtDrawerCreator : public BaseDrawerCreator
{
    public:
        QtDrawerCreator() = delete;
        explicit QtDrawerCreator(std::shared_ptr<QGraphicsScene> scene);
        virtual ~QtDrawerCreator() override = default;

        std::unique_ptr<BaseDrawer> createDrawer() override;

    private:
        std::shared_ptr<QGraphicsScene> m_scene;
};