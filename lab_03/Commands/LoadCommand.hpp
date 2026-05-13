#pragma once

#include <string>
#include "BaseCommand.hpp"
#include "ManagerSolution.hpp"
#include "SceneManager.hpp"
#include "LoadManager.hpp"
#include "MatrixBuilder.hpp"
#include "ListBuilder.hpp"


class LoadCommand : public BaseCommand
{
    public:
        LoadCommand() = default;
        virtual ~LoadCommand() override = default;
};

class LoadMatrixModelCommand : public LoadCommand
{
    public:
        LoadMatrixModelCommand(const std::string &filename) : m_filename(filename) {}
        virtual ~LoadMatrixModelCommand() override = default;

        void execute() override
        {
            auto loadManager = ManagerSolution::getManager<LoadManager>();
            loadManager->load<MatrixBuilder>(m_filename);
        }

    private:
        std::string m_filename;
};

class LoadListModelCommand : public LoadCommand
{
    public:
        LoadListModelCommand(const std::string &filename) : m_filename(filename) {}
        virtual ~LoadListModelCommand() override = default;

        // TODO мне не нравится что тут вызываются оба менеджера: LoadManager и SceneManager

        void execute() override
        {
            auto loadManager = ManagerSolution::getManager<LoadManager>();
            auto sceneManager = ManagerSolution::getManager<SceneManager>();

            auto model = loadManager->load<ListBuilder>(m_filename);
            sceneManager->addObject(model);
        }

    private:
        std::string m_filename;
};