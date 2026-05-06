#pragma once

#include <vector>
#include "BaseStructure.hpp"
#include "ModelException.hpp"


class MatrixStructure : public BaseStructure
{
    public:
        MatrixStructure();
        virtual ~MatrixStructure() override = default;

        void addVertex(const Vertex &vertex) override;
        void addEdge(const Edge &edge) override;

        void transform(const Transform &action) override;

        void setCenter(const Vertex &point) override;

        Vertex getCenter() const noexcept override;
        std::vector<Edge> getEdges() const noexcept override;
        std::vector<Vertex> getVertices() noexcept override;

    private:
        std::vector<Vertex> m_vertices;
        std::vector<std::vector<bool>> m_adjacencyMatrix;
        size_t m_vertexQuantity;

        void resizeMatrix(size_t newSize);
};