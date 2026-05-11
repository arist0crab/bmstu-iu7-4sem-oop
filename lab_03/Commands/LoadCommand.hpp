#pragma once

#include <iostream>
#include "BaseCommand.hpp"
#include "ManagerSolution.hpp"


class LoadCommand : public BaseCommand
{
    public:
        LoadCommand() = default;
        virtual ~LoadCommand() = default;
};


class LoadMatrixModelCommand : public LoadCommand
{
    public:
        LoadMatrixModelCommand(const std::string &filename) : m_filename(filename) {}
        virtual ~LoadMatrixModelCommand() override = default;

        void execute() override
        {
            // TODO write managers
            // auto loadManager = ManagerSolution::getManager<LoadManager>();
            // loadManager->
        }

    private:
        std::string m_filename;
};


class LoadListModelCommand : public LoadCommand
{
    public:
        LoadListModelCommand(const std::string &filename) : m_filename(filename) {}
        virtual ~LoadListModelCommand() override = default;

        void execute() override
        {
            // TODO write managers
            // auto loadManager = ManagerSolution::getManager<LoadManager>();
            // loadManager->
        }

    private:
        std::string m_filename;
};