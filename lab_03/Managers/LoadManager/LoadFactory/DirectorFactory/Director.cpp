#include "Director.hpp"


void Director::setBuilder(std::shared_ptr<BaseBuilder> builder)
{
    m_builder = builder;
}

void Director::setReader(std::shared_ptr<BaseReader> reader)
{
    m_reader = reader;
}

std::shared_ptr<BaseObject> Director::build(const std::string &filename)
{
    m_reader->open(filename);

    auto vertices = m_reader->readVertices();
    auto edges = m_reader->readEdges();

    for (auto &v : vertices)
        m_builder->buildVertex(v);

    for (auto &e : edges)
        m_builder->buildEdge(e.getStart(), e.getEnd());

    m_reader->close();

    return m_builder->getResult();
}
