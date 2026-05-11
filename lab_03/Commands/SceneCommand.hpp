#pragma once

#include "BaseCommand.hpp"
#include "DrawManager.hpp"
#include "ManagerSolution.hpp"


class SceneCommand : public BaseCommand
{
    SceneCommand() = default;
    virtual ~SceneCommand() override = default;
};


class DrawSceneCommand : public SceneCommand
{
    public:
        DrawSceneCommand() = default;
        virtual ~DrawSceneCommand() override = default;

        void execute() override
        {
            auto drawManager = ManagerSolution::getManager<DrawManager>();
            drawManager->draw();
        }
};


class ClearSceneCommand : public SceneCommand
{
    public:
        ClearSceneCommand() = default;
        virtual ~ClearSceneCommand() override = default;

        void execute() override
        {
            // TODO auto sceneManager = ManagerSolution::getManager<SceneManager>();
            // TODO sceneManager->clear();
        }
};