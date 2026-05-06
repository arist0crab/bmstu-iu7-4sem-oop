#include <cstddef> 

using vertex_index_t = size_t;

class Edge
{
    public:
        Edge() = default;
        Edge(Edge &&edge) = default;
        Edge(const Edge &edge) = default;
        Edge(vertex_index_t start, vertex_index_t end);
        virtual ~Edge() = default;

        Edge &operator=(const Edge &) = default;
        Edge &operator=(Edge &&) = default;

        vertex_index_t getStart() const;
        vertex_index_t getEnd() const;

        void setStart(vertex_index_t start);
        void setEnd(vertex_index_t end);

    private:
        vertex_index_t m_start, m_end;    
};