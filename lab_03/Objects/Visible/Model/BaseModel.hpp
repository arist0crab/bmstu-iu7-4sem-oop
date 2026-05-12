#pragma once

#include <memory>
#include "VisibleObject.hpp"
#include "BaseStructure.hpp"

class BaseModel : public VisibleObject
{
    public:
        BaseModel() = default;
        explicit BaseModel(std::shared_ptr<BaseStructure> structure);
        virtual ~BaseModel() override = default;

        Vertex getCenter() const noexcept;
        std::vector<Vertex> getVertices() const;
        std::vector<Edge> getEdges() const;

        void setCenter(const Vertex &point);
        void transform(const Transform &transform);

        std::shared_ptr<BaseStructure> getStructure() const;

    protected:
        std::shared_ptr<BaseStructure> m_structure;
};