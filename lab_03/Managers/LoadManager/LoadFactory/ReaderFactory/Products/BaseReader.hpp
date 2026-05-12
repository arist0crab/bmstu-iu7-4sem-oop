#pragma once

#include <string>
#include <vector>
#include <Vertex.hpp>
#include <Edge.hpp>


class BaseReader 
{
    public:
        BaseReader() = default;
        virtual ~BaseReader() = default;

        virtual void open(const std::string &filename) = 0;
        virtual void close() = 0;

        virtual std::vector<Vertex> readVertices() = 0;
        virtual std::vector<Edge> readEdges() = 0;
};