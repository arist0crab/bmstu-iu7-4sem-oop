#pragma once

#include "BaseVisitorCreator.hpp"
#include "TransformVisitor.hpp"


class TransformVisitorCreator : public BaseVisitorCreator
{
    public:
        TransformVisitorCreator(const Transform &transform) : m_transform(transform) {}
        virtual ~TransformVisitorCreator() override = default;

        std::shared_ptr<BaseVisitor> create() override
        {
            return std::make_shared<TransformVisitor>(m_transform);
        }

    private:
        Transform m_transform;
};