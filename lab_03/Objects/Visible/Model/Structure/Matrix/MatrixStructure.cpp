#include "MatrixStructure.hpp"


MatrixStructure::MatrixStructure() : m_vertices(), m_adjacencyMatrix(), m_vertexQuantity(0) { }

void MatrixStructure::addVertex(const Vertex &vertex)
{
    m_vertices.push_back(vertex);
    m_vertexQuantity = m_vertices.size();

    if (m_vertexQuantity >= m_adjacencyMatrix.size())
        resizeMatrix(m_vertexQuantity * 2);
}

void MatrixStructure::addEdge(const Edge &edge)
{
    size_t id1 = edge.getStart();
    size_t id2 = edge.getEnd();

    if (id1 >= m_vertexQuantity || id2 >= m_vertexQuantity)
        throw ModelInvalidEdgeException(MODEL_EDGE_INDEX_OUT_OF_RANGE_ERR);

    m_adjacencyMatrix[id1][id2] = true;
    m_adjacencyMatrix[id2][id1] = true;
}

void MatrixStructure::transform(const Transform &action)
{
    m_localTransform *= action;
}

void MatrixStructure::setCenter(const Vertex &point)
{
    const double dx = point.X();
    const double dy = point.Y();
    const double dz = point.Z();
    m_localTransform.setTranslation(dx, dy, dz);
}

Vertex MatrixStructure::getCenter() const noexcept
{
    Vertex world_center = m_localCenter;
    world_center.transform(m_localTransform);

    return world_center;
}

std::vector<Edge> MatrixStructure::getEdges() const noexcept
{
    std::vector<Edge> edges;

    for (size_t i = 0; i < m_vertexQuantity; i++)
        for (size_t j = i + 1; j < m_vertexQuantity; j++)
            if (m_adjacencyMatrix[i][j])
                edges.emplace_back(i, j);

    return edges;
}

std::vector<Vertex> MatrixStructure::getVertices() noexcept
{
    std::vector<Vertex> world_vertices = m_vertices; 

    for (Vertex &v : world_vertices)
        v.transform(m_localTransform); 

    return world_vertices;
}

void MatrixStructure::resizeMatrix(size_t newSize)
{
    for (auto &row : m_adjacencyMatrix)
        row.resize(newSize, false);

    for (size_t i = m_adjacencyMatrix.size(); i < newSize; i++)
        m_adjacencyMatrix.emplace_back(newSize, false);    
}
