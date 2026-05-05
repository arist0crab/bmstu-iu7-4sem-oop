#pragma once

#include <memory>

class BaseCamera;
class BaseModel;

class BaseVisitor
{
    public:
        BaseVisitor() = default;
        virtual ~BaseVisitor() = default;

        virtual void visit(BaseModel &model) const = 0;
        virtual void visit(BaseCamera &camera) const = 0;
};