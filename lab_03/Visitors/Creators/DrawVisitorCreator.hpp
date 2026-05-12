#pragma once

#include "BaseVisitorCreator.hpp"


template <typename TVisitor>
class DrawVisitorCreator : public BaseVisitorCreator
{
    public:
        DrawVisitorCreator() = default;
        virtual ~DrawVisitorCreator() override = default;

        std::shared_ptr<BaseVisitor> create() override
        {
            return std::make_shared<TVisitor>();
        }
};