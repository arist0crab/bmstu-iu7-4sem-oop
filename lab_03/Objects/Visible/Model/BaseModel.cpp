#include "BaseModel.hpp"


BaseModel::BaseModel(std::shared_ptr<BaseStructure> structure) : m_structure(structure) 
{ 
    if (m_structure)
        m_center = m_structure->getCenter();
}

std::vector<Vertex> BaseModel::getVertices() const
{
    return m_structure->getVertices();
}

std::vector<Edge> BaseModel::getEdges() const
{
    return m_structure->getEdges();
}

std::shared_ptr<BaseStructure> BaseModel::getStructure() const
{
    return m_structure;
}