#include "Vertex.hpp"


class BasePainter
{
    public:
        BasePainter() = default;
        virtual ~BasePainter() = default;

        virtual size_t getWidth() const noexcept = 0;
        virtual size_t getHeight() const noexcept = 0;

        virtual void clear() = 0;
        virtual void drawLine(const Vertex &v1, const Vertex &v2) = 0;

    protected:
        size_t m_sceneWidth;
        size_t m_sceneHeight;
};