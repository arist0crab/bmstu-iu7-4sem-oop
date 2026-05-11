#include "BaseModel.hpp"

BaseModel::BaseModel(std::shared_ptr<BaseStructure> structure) : m_structure(structure) { }

Vertex BaseModel::getCenter() const noexcept
{
    return m_structure->getCenter();
}

void BaseModel::setCenter(const Vertex &point)
{
    m_structure->setCenter(point);
}

void BaseModel::transform(const Transform &transform)
{
    m_structure->transform(transform);
}

std::shared_ptr<BaseStructure> BaseModel::getStructure() const
{
    return m_structure;
}