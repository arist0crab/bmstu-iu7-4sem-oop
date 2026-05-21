#include "CarcassModel.hpp"
#include "BaseVisitor.hpp"

CarcassModel::CarcassModel(std::shared_ptr<BaseStructure> structure) : BaseModel(structure) { }

void CarcassModel::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(*this);
}