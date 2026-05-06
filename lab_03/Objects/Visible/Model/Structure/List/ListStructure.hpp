#pragma once

#include "BaseStructure.hpp"


class ListStructure : public BaseStructure
{
    public:
        ListStructure();
        virtual ~ListStructure() override = default;

        void addVertex(const Vertex &vertex) override;
        void addEdge(const Edge &edge) override;

        void transform(const Transform &action) override;

        void setCenter(const Vertex &point) override;

        Vertex getCenter() const noexcept override;
        std::vector<Edge> getEdges() const noexcept override;
        std::vector<Vertex> getVertices() noexcept override;

    private:
        std::vector<Vertex> m_vertices;
        std::vector<Edge> m_edges;
};