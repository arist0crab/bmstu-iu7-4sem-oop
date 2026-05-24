#include "TransformVisitor.hpp"
#include "BaseCamera.hpp"
#include "BaseStructure.hpp"

TransformVisitor::TransformVisitor(const Transform &transform) : m_transform(transform) { }

void TransformVisitor::visit(BaseCameraImplementation &camera) const
{
    camera.transform(m_transform);
}

void TransformVisitor::visit(BaseStructure &structure) const
{
    structure.transform(m_transform);
}