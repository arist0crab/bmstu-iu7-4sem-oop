#include "DrawCarcassVisitor.hpp"

void DrawCarcassVisitor::visit(BaseCameraImplementation &camera) const { }

void DrawCarcassVisitor::visit(BaseStructure &structure) const
{
    if (!m_camera || !m_drawer) 
        return;

    auto vertices = structure.getVertices();
    auto edges = structure.getEdges();

    double aspect = 1.0; 
    Transform viewMatrix = m_camera->getViewMatrix();
    Transform projMatrix = m_camera->getProjectionMatrix(aspect);
    Transform viewProjection = viewMatrix * projMatrix;

    for (auto &edge : edges)
    {
        Vertex v1 = vertices[edge.getStart()];
        Vertex v2 = vertices[edge.getEnd()];

        v1.transform(viewProjection);
        v2.transform(viewProjection);

        m_drawer->drawLine(v1, v2); 
    }
}