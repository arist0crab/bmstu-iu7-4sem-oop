#pragma once

#include "Vertex.hpp"
#include "Edge.hpp"
#include <memory>
#include <vector>

class BaseStructure
{
    public:
        BaseStructure();
        virtual ~BaseStructure() = default;

        virtual void addVertex(const Vertex &vertex) = 0;
        virtual void addEdge(const Edge &edge) = 0;

        virtual void transform(const Transform &action) = 0;

        virtual void setCenter(const Vertex &point) = 0;

        virtual Vertex getLocalCenter() const noexcept;
        virtual Transform getLocalTransform() const noexcept;
        virtual Vertex getCenter() const noexcept = 0;
        virtual std::vector<Edge> getEdges() const noexcept = 0;
        virtual std::vector<Vertex> getVertices() noexcept = 0;
    
    protected:
        Vertex m_localCenter;
        Transform m_localTransform;
};