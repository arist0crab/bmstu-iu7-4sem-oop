#pragma once

#include "BaseCommand.hpp"
#include "ManagerSolution.hpp"
#include "DrawManager.hpp"
#include "DrawCarcassVisitor.hpp"


class SceneCommand : public BaseCommand
{
    public:
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
            auto visitor = std::make_shared<DrawCarcassVisitor>();
            drawManager->draw(visitor);
        }
};

class ClearSceneCommand : public SceneCommand
{
    public:
        ClearSceneCommand() = default;
        virtual ~ClearSceneCommand() override = default;

        void execute() override
        {
            auto sceneManager = ManagerSolution::getManager<SceneManager>();
            sceneManager->clear();
        }
};