#include "CarcassModel.hpp"
#include "BaseVisitor.hpp"

CarcassModel::CarcassModel(std::shared_ptr<BaseStructure> structure) : BaseModel(structure) { }

void CarcassModel::accept(std::shared_ptr<BaseVisitor> visitor)
{
    if (m_structure)
        visitor->visit(*m_structure); 
}