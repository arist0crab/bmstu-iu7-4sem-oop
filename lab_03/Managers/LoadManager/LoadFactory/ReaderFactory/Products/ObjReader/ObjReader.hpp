#pragma once

#include "BaseReader.hpp"
#include <fstream>
#include <sstream>


class ObjReader : public BaseReader
{   
    public:
        ObjReader() = default;
        virtual ~ObjReader() override = default;

        void open(const std::string &filename) override;
        void close() override;
        
        std::vector<Vertex> readVertices() override;
        std::vector<Edge> readEdges() override;

    private:
        std::ifstream m_file;
};