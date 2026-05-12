#include "ObjReader.hpp"


void ObjReader::open(const std::string &filename)
{
    m_file.open(filename);
    if (!m_file.is_open())
        // TODO add custom errors
        throw std::runtime_error("Cannot open file: " + filename);
}

void ObjReader::close()
{
    if (m_file.is_open())
        m_file.close();
}

std::vector<Vertex> ObjReader::readVertices()
{
    std::vector<Vertex> vertices;
    std::string line;
    
    while (std::getline(m_file, line))
    {
        if (line.empty() || line[0] != 'v' || line[1] != ' ')
            continue;
        
        std::istringstream iss(line.substr(2));
        double x, y, z;
        
        if (iss >> x >> y >> z)
            vertices.emplace_back(x, y, z);
    }
    
    return vertices;
}

std::vector<Edge> ObjReader::readEdges()
{
    std::vector<Edge> edges;
    std::string line;
    
    m_file.clear();
    m_file.seekg(0);
    
    while (std::getline(m_file, line))
    {
        if (line.empty() || line[0] != 'f' || line[1] != ' ')
            continue;
        
        std::istringstream iss(line.substr(2));
        std::vector<size_t> indices;
        std::string part;
        
        while (iss >> part)
        {
            size_t idx = std::stoi(part.substr(0, part.find('/'))) - 1;
            indices.push_back(idx);
        }
        
        for (size_t i = 0; i < indices.size(); ++i)
            edges.emplace_back(indices[i], indices[(i + 1) % indices.size()]);
    }
    
    return edges;
}