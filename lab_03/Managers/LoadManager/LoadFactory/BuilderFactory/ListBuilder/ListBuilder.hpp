#pragma once

#include "BaseBuilder.hpp"
#include "ListStructure.hpp"
#include "CarcassModel.hpp"

class ListBuilder : public BaseBuilder
{
    public:
        ListBuilder();
        virtual ~ListBuilder() override = default;

        void buildVertex(const Vertex &vertex) override;
        void buildEdge(size_t start, size_t end) override;
        std::shared_ptr<BaseObject> getResult() override;

    private:
        std::shared_ptr<ListStructure> m_structure;
};