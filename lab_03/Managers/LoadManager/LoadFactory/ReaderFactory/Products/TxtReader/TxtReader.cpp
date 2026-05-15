#include "TxtReader.hpp"
#include "TxtReaderException.hpp"


void TxtReader::open(const std::string &filename)
{
    m_file.open(filename);
    if (!m_file.is_open())
        throw TxtReaderFileNotFoundException();
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
    
    if (!(m_file >> count))
        throw TxtReaderParseException("Failed to read vertices count");

    std::getline(m_file, line);
    
    for (size_t i = 0; i < count; ++i)
    {
        double x, y, z;
        if (!(m_file >> x >> y >> z))
            throw TxtReaderParseException("Failed to parse vertex");
        
        vertices.emplace_back(x, y, z);
    }
    
    return vertices;
}

std::vector<Edge> TxtReader::readEdges()
{
    std::vector<Edge> edges;
    std::string line;
    size_t count = 0;
    
    if (!(m_file >> count))
        throw TxtReaderParseException("Failed to read edges count");

    std::getline(m_file, line);
    
    for (size_t i = 0; i < count; ++i)
    {
        size_t start, end;
        if (!(m_file >> start >> end))
            throw TxtReaderParseException("Failed to parse edge");

        edges.emplace_back(start, end);
    }
    
    return edges;
}