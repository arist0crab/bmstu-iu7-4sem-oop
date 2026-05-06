#include "ListStructure.hpp"

ListStructure::ListStructure() : m_vertices(std::vector<Vertex>()), m_edges(std::vector<Edge>()) { }

void ListStructure::addVertex(const Vertex &vertex)
{
    m_vertices.push_back(vertex);
}

void ListStructure::addEdge(const Edge &edge)
{
    m_edges.push_back(edge);
}

void ListStructure::transform(const Transform &action)
{
    m_localTransform *= action;
}

void ListStructure::setCenter(const Vertex &point)
{
    const double dx = point.X();
    const double dy = point.Y();
    const double dz = point.Z();
    m_localTransform.setTranslation(dx, dy, dz);
}

Vertex ListStructure::getCenter() const noexcept
{
    Vertex world_center = m_localCenter;
    world_center.transform(m_localTransform);

    return world_center;
}

std::vector<Edge> ListStructure::getEdges() const noexcept
{
    return m_edges;
}

std::vector<Vertex> ListStructure::getVertices() noexcept
{
    std::vector<Vertex> world_vertices = m_vertices; 

    for (Vertex &v : world_vertices)
        v.transform(m_localTransform); 

    return world_vertices;
}