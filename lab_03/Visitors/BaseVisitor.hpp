#pragma once

#include <memory>

class BaseCameraImplementation;
class BaseStructure;

class BaseVisitor
{
    public:
        BaseVisitor() = default;
        virtual ~BaseVisitor() = default;

        virtual void visit(BaseCameraImplementation &camera) const = 0;
        virtual void visit(BaseStructure &structure) const = 0;
};