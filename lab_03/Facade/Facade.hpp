#pragma once

#include <memory>
#include "BaseCommand.hpp"


class Facade
{
    public:
        Facade() = default;
        ~Facade() = default;

        void execute(const std::shared_ptr<BaseCommand> &command);
};