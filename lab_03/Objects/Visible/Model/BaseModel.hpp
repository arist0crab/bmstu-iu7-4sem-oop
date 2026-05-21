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

        std::vector<Edge> getEdges() const;
        std::vector<Vertex> getVertices() const;

        std::shared_ptr<BaseStructure> getStructure() const;

    protected:
        std::shared_ptr<BaseStructure> m_structure;
};