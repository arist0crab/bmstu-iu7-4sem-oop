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

        std::shared_ptr<BaseStructure> getStructure() const;

    protected:
        std::shared_ptr<BaseStructure> m_structure;
};