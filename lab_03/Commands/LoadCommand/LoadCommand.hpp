#pragma once

#include <string>
#include "BaseCommand.hpp"
#include "BaseObject.hpp"


class LoadCommand : public BaseCommand
{
    public:
        LoadCommand() = default;
        virtual ~LoadCommand() override = default;
};

class LoadMatrixModelCommand : public LoadCommand
{
    public:
        LoadMatrixModelCommand(const std::string &filename);
        virtual ~LoadMatrixModelCommand() override = default;

        void execute() override;

    private:
        using Action = std::shared_ptr<BaseObject> (LoadManager::*)(const std::string &);
        using SceneAction = void (SceneManager::*)(std::shared_ptr<BaseObject>);

        Action m_loadAction;
        SceneAction m_sceneAction;
        std::string m_filename;
};

class LoadListModelCommand : public LoadCommand
{
    public:
        LoadListModelCommand(const std::string &filename);
        virtual ~LoadListModelCommand() override = default;

        void execute() override;

    private:
        using Action = std::shared_ptr<BaseObject> (LoadManager::*)(const std::string &);
        using SceneAction = void (SceneManager::*)(std::shared_ptr<BaseObject>);
        
        Action m_loadAction;
        SceneAction m_sceneAction;
        std::string m_filename;
};