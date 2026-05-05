#include "Facade.hpp"


void Facade::execute(const std::shared_ptr<BaseCommand> &command)
{
    command->execute();
}