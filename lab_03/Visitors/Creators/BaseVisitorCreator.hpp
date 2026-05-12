#pragma once

#include <memory>
#include "BaseVisitor.hpp"


class BaseVisitorCreator
{
    public:
        BaseVisitorCreator() = default;
        virtual ~BaseVisitorCreator() = default;

        virtual std::shared_ptr<BaseVisitor> create() = 0;
};