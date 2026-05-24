#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "BaseBuilder.hpp"
#include "ListBuilder.hpp"
#include "MatrixBuilder.hpp"

class BuilderSolution
{
    public:
        static std::shared_ptr<BaseBuilder> create(const std::string &type)
        {
            static const std::unordered_map<std::string, std::shared_ptr<BaseBuilder>> builders = {
                {"list", std::make_shared<ListBuilder>()},
                {"matrix", std::make_shared<MatrixBuilder>()}
            };

            auto it = builders.find(type);
            return (it != builders.end()) ? it->second : nullptr;
        }
};