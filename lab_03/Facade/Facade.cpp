#include "Facade.hpp"


Facade::Facade() : m_managerSolution(std::make_shared<ManagerSolution>()) { }

void Facade::execute(const std::shared_ptr<BaseCommand> &command)
{
    command->execute();
}