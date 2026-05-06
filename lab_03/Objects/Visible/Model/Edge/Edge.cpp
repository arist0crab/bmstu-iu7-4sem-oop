#include "Edge.hpp"

Edge::Edge(vertex_index_t start, vertex_index_t end) : m_start(start), m_end(end) { }

vertex_index_t Edge::getStart() const
{
    return m_start;
}
vertex_index_t Edge::getEnd() const
{
    return m_end;
}

void Edge::setStart(vertex_index_t start)
{
    m_start = start;
}

void Edge::setEnd(vertex_index_t end)
{
    m_end = end;
}
