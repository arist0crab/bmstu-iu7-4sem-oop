#pragma once

#include <memory>
#include "BaseManager.hpp"

class DrawManager : public BaseManager
{
    public:
        DrawManager() = default;
        virtual ~DrawManager() override = default;
        void setPainter(std::shared_ptr<BasePainter> painter);

    private:
        std::shared_ptr<BasePainter> m_painter;
};
