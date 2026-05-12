#include "ListBuilder.hpp"


ListBuilder::ListBuilder()
{
    m_structure = std::make_shared<ListStructure>();
}

void ListBuilder::buildVertex(const Vertex &vertex)
{
    m_structure->addVertex(vertex);
}

void ListBuilder::buildEdge(size_t start, size_t end)
{
    m_structure->addEdge(Edge(start, end));
}

std::shared_ptr<BaseObject> ListBuilder::getResult()
{
    return std::make_shared<CarcassModel>(m_structure);
}