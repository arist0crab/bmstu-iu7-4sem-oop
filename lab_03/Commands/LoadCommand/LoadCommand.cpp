#include "LoadCommand.hpp"
#include "LoadManager.hpp"


LoadMatrixModelCommand::LoadMatrixModelCommand(const std::string &filename) : m_filename(filename), m_action(&LoadManager::load) {}

void LoadMatrixModelCommand::execute()
{
    ((*m_loadManager).*m_action)(m_filename, "matrix");
}

LoadListModelCommand::LoadListModelCommand(const std::string &filename) : m_filename(filename), m_action(&LoadManager::load) {}

void LoadListModelCommand::execute()
{
    ((*m_loadManager).*m_action)(m_filename, "list");
}