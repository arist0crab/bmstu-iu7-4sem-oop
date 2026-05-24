#pragma once

#include <memory>
#include <QGraphicsScene>
#include "BaseDrawerFactory.hpp"

class QtDrawerFactory final : public BaseDrawerFactory
{
    public:
        QtDrawerFactory() = delete;
        explicit QtDrawerFactory(std::shared_ptr<QGraphicsScene> scene);
        ~QtDrawerFactory() override = default;

        std::unique_ptr<BaseDrawer> createDrawer() const override;

    private:
        std::shared_ptr<QGraphicsScene> m_scene;
};