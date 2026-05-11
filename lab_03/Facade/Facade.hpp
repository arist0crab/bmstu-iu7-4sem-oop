#pragma once

#include <memory>
#include "BaseCommand.hpp"
#include "ManagerSolution.hpp"


class Facade
{
    public:
        Facade();
        ~Facade() = default;

        void execute(const std::shared_ptr<BaseCommand> &command);
    
    private:
        std::shared_ptr<ManagerSolution> m_managerSolution;
};