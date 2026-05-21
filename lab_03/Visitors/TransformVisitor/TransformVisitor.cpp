#include "TransformVisitor.hpp"
#include "BaseCamera.hpp"
#include "BaseModel.hpp"


TransformVisitor::TransformVisitor(const Transform &transform) : m_transform(transform) { }

void TransformVisitor::visit(BaseCamera &camera) const
{
    camera.transform(m_transform);
}

void TransformVisitor::visit(BaseModel &model) const
{
    Vertex center = model.getCenter();
    center.transform(m_transform); 
    model.setCenter(center);

    auto structure = model.getStructure();
    if (structure)
        structure->transform(m_transform);
}