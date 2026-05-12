#pragma once

#include <memory>
#include "BaseObject.hpp"
#include "Vertex.hpp"


class BaseBuilder
{
    public:
        BaseBuilder() = default;
        virtual ~BaseBuilder() = default;

        virtual void buildVertex(const Vertex &vertex) = 0;
        virtual void buildEdge(size_t start, size_t end) = 0;
        virtual std::shared_ptr<BaseObject> getResult() = 0;
};