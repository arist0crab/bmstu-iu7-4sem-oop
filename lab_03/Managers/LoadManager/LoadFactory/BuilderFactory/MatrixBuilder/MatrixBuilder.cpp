#include "MatrixBuilder.hpp"


MatrixBuilder::MatrixBuilder()
{
    m_structure = std::make_shared<MatrixStructure>();
}

void MatrixBuilder::buildVertex(const Vertex &vertex)
{
    m_structure->addVertex(vertex);
}

void MatrixBuilder::buildEdge(size_t start, size_t end)
{
    m_structure->addEdge(Edge(start, end));
}

std::shared_ptr<BaseObject> MatrixBuilder::getResult()
{
    return std::make_shared<CarcassModel>(m_structure);
}