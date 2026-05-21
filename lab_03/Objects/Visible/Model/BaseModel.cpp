#include "BaseModel.hpp"


BaseModel::BaseModel(std::shared_ptr<BaseStructure> structure) : m_structure(structure) 
{ 
    if (m_structure)
        m_center = m_structure->getCenter();
}

std::shared_ptr<BaseStructure> BaseModel::getStructure() const
{
    return m_structure;
}