#pragma once

#include <memory>
#include <string>
#include "BaseManager.hpp"
#include "BaseObject.hpp"

class LoadManager : public BaseManager
{
    public:
        LoadManager() = default;
        ~LoadManager() override = default;

        std::shared_ptr<BaseObject> load(const std::string &filename, const std::string &builderType);
};