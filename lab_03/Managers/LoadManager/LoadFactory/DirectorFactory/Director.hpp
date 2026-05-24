#pragma once

#include <memory>
#include <string>
#include "BaseObject.hpp"

class Director
{
    public:
        Director() = default;
        ~Director() = default;

        std::shared_ptr<BaseObject> build(const std::string &filename, const std::string &builderType);
};