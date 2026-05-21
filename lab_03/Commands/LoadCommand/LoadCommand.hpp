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
        using Action = void (LoadManager::*)(const std::string &);

        Action m_Action;
        std::string m_filename;
};

class LoadListModelCommand : public LoadCommand
{
    public:
        LoadListModelCommand(const std::string &filename);
        virtual ~LoadListModelCommand() override = default;

        void execute() override;

    private:
        using Action = void (LoadManager::*)(const std::string &);
        
        Action m_Action;
        std::string m_filename;
};