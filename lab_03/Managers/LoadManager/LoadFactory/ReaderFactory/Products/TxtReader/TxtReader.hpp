#pragma once

#include <fstream>
#include <sstream>
#include "BaseReader.hpp"


class TxtReader : public BaseReader
{
    public:
        TxtReader() = default;
        virtual ~TxtReader() override = default;

        void open(const std::string &filename) override;
        void close() override;

        std::vector<Vertex> readVertices() override;
        std::vector<Edge> readEdges() override;
    
    private:
        std::ifstream m_file;
};