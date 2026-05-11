#pragma once

#include "BaseModel.hpp"
#include "BaseStructure.hpp"
#include "Vertex.hpp"


class CarcassModel final : public BaseModel
{
    public:
        CarcassModel() = default;
        explicit CarcassModel(std::shared_ptr<BaseStructure> structure);
        virtual ~CarcassModel() override = default;

        void accept(std::shared_ptr<BaseVisitor> visitor) override;
};