#include "LoadCommand.hpp"
#include "LoadManager.hpp"
#include "ManagerSolution.hpp"

LoadMatrixModelCommand::LoadMatrixModelCommand(const std::string &filename) : m_filename(filename) {}

void LoadMatrixModelCommand::execute()
{
    auto loadManager = ManagerSolution::getManager<LoadManager>();
    loadManager->load(m_filename, "matrix");
}

LoadListModelCommand::LoadListModelCommand(const std::string &filename) : m_filename(filename) {}

void LoadListModelCommand::execute()
{
    auto loadManager = ManagerSolution::getManager<LoadManager>();
    loadManager->load(m_filename, "list");
}