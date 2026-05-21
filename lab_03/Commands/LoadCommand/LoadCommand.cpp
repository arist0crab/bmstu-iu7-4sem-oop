#include "LoadCommand.hpp"
#include "LoadManager.hpp"

LoadMatrixModelCommand::LoadMatrixModelCommand(const std::string &filename) : m_filename(filename), m_Action(&LoadManager::loadMatrixModel) {}

void LoadMatrixModelCommand::execute()
{
    ((*m_loadManager).*m_Action)(m_filename);
}

LoadListModelCommand::LoadListModelCommand(const std::string &filename) : m_filename(filename), m_Action(&LoadManager::loadListModel) {}

void LoadListModelCommand::execute()
{
    ((*m_loadManager).*m_Action)(m_filename);
}