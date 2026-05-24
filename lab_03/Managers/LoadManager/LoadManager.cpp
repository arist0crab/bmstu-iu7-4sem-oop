#include "LoadManager.hpp"
#include "ManagerSolution.hpp"
#include "SceneManager.hpp"
#include "Director.hpp"


std::shared_ptr<BaseObject> LoadManager::load(const std::string &filename, const std::string &builderType)
{
    Director director;
    
    auto sceneManager = ManagerSolution::getManager<SceneManager>();
    auto model = director.build(filename, builderType);
    sceneManager->addObject(model);

    return model;
}