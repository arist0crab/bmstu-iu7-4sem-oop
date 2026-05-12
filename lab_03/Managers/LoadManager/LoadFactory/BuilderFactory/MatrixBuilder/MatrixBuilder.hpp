#pragma once

#include "BaseBuilder.hpp"
#include "MatrixStructure.hpp"
#include "CarcassModel.hpp"


class MatrixBuilder : public BaseBuilder
{
    public:
        MatrixBuilder();
        virtual ~MatrixBuilder() override = default;

        void buildVertex(const Vertex &vertex) override;
        void buildEdge(size_t start, size_t end) override;
        std::shared_ptr<BaseObject> getResult() override;

    private:
        std::shared_ptr<MatrixStructure> m_structure;
};