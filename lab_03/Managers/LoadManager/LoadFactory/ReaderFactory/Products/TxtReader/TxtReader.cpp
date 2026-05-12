#include "TxtReader.hpp"


void TxtReader::open(const std::string &filename)
{
    m_file.open(filename);
    // TODO add custom errors
    if (!m_file.is_open())
        throw std::runtime_error("Cannot open file: " + filename);
}

void TxtReader::close()
{
    if (m_file.is_open())
        m_file.close();
}

std::vector<Vertex> TxtReader::readVertices()
{
    std::vector<Vertex> vertices;
    std::string line;
    size_t count = 0;
    
    m_file >> count;
    std::getline(m_file, line);
    
    for (size_t i = 0; i < count; ++i)
    {
        double x, y, z;
        m_file >> x >> y >> z;
        vertices.emplace_back(x, y, z);
    }
    
    return vertices;
}

std::vector<Edge> TxtReader::readEdges()
{
    std::vector<Edge> edges;
    std::string line;
    size_t count = 0;
    
    m_file >> count;
    std::getline(m_file, line);
    
    for (size_t i = 0; i < count; ++i)
    {
        size_t start, end;
        m_file >> start >> end;
        edges.emplace_back(start, end);
    }
    
    return edges;
}