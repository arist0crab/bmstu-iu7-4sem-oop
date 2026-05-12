#include "DrawCarcassVisitor.hpp"

void DrawCarcassVisitor::visit(BaseCamera &camera) const { }

void DrawCarcassVisitor::visit(BaseModel &model) const
{
    auto vertices = model.getVertices();
    auto edges = model.getEdges();

    for (auto &edge : edges)
    {
        auto v1 = vertices[edge.getStart()];
        auto v2 = vertices[edge.getEnd()];

        m_drawer->drawLine(v1, v2);
    }
}