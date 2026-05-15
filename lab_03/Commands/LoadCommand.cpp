#include "LoadCommand.hpp"
#include "LoadManager.hpp"
#include "SceneManager.hpp"


LoadMatrixModelCommand::LoadMatrixModelCommand(const std::string &filename)
    : m_filename(filename)
    , m_loadAction(&LoadManager::load<MatrixBuilder>)
    , m_sceneAction(&SceneManager::addObject) {}

void LoadMatrixModelCommand::execute()
{
    auto model = ((*m_loadManager).*m_loadAction)(m_filename);
    ((*m_sceneManager).*m_sceneAction)(model);
}

LoadListModelCommand::LoadListModelCommand(const std::string &filename)
    : m_filename(filename)
    , m_loadAction(&LoadManager::load<ListBuilder>)
    , m_sceneAction(&SceneManager::addObject) {}

void LoadListModelCommand::execute()
{
    auto model = ((*m_loadManager).*m_loadAction)(m_filename);
    ((*m_sceneManager).*m_sceneAction)(model);
}